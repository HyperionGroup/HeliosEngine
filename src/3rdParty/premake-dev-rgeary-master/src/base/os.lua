--
-- os.lua
-- Additions to the OS namespace.
-- Copyright (c) 2002-2011 Jason Perkins and the Premake project
--

-- Other os.X functions available, implemented in C :
--
-- os.stat(filename)	
--		Returns { mtime = <Last modified time in ms>, size = <file size in bytes> }  
--
-- os.chdir(dir)
--		Change the current working directory
--
-- os.chmod(filename, octal mode as string)
--		Sets the file permissions, eg. os.chmod(filename, "777")
--
-- os.copyfile(src, dest)
--		Copy a file using the default operating system C function
--
-- os.getcwd()
--		Returns the canonical current working directory. Use _CWD for the current working directory including symlinks.
--
-- os.is64bit()
--		Returns true if the platform is 64bit
--
-- os.isdir(dir)
--		Returns true if dir is a directory
--
-- os.isfile(filename)
--		Returns true if filename is a file
--
-- os.mkdir(dir)
--		Creates a new directory (not recursive)
--      This os.lua file overrides this to make it recursive
--
-- os.rmdir(dir)
--		Removes directory dir (not recursive)
--
-- os.uuid()
--		Creates a new GUID


--
-- Same as os.execute(), but accepts string formatting arguments.
--

	function os.executef(cmd, ...)
		if repoRoot then
			cmd = cmd:replace('$root/', repoRoot)
		end
		cmd = string.format(cmd, unpack(arg))
		return os.execute(cmd)
	end
	
	local builtin_execute = os.execute
	function os.execute(cmd)
		if( _OPTIONS['dryrun'] ) then	
			print("Execute : " ..cmd)
			return 0 
		else
			return builtin_execute(cmd)
		end
	end
	
--
-- Override to replace $root with repoRoot
--
	local builtin_isfile = os.isfile
	function os.isfile(s)
		if not s then 
			return false 
		end
		if repoRoot then
			s = s:replace('$root/', repoRoot)
		end
		return builtin_isfile(s)
	end

	local builtin_isdir = os.isdir
	function os.isdir(s)
		if not s then 
			return false 
		end
		if repoRoot then
			s = s:replace('$root/', repoRoot)
		end
		return builtin_isdir(s)
	end
	
	function os.exists(path)
		path = path:replace('$root/', repoRoot or '')
		return (os.stat(path) ~= nil)
	end

--
-- Scan the well-known system locations for a particular library. 
--  Add to the search path using premake.libsearchpath
--

	function os.findlib(libname)
		local path, formats
		local delimiter = ':'

		-- assemble a search path, depending on the platform
		if os.is("windows") then
			formats = { "%s.dll", "%s" }
			path = os.getenv("PATH")
			delimiter = ';'
		elseif os.is("haiku") then
			formats = { "lib%s.so", "%s.so" }
			path = os.getenv("LIBRARY_PATH")
		else
			if os.is("macosx") then
				formats = { "lib%s.dylib", "%s.dylib" }
				path = os.getenv("DYLD_LIBRARY_PATH")
			else
				formats = { "lib%s.so", "%s.so" }
				path = os.getenv("LD_LIBRARY_PATH") or ""

				io.input("/etc/ld.so.conf")
				if io.input() then
					for line in io.lines() do
						path = path .. ":" .. line
					end
					io.input():close()
				end
			end

			table.insert(formats, "%s")
			path = path or ""
			if os.is64bit() then
				path = path .. ":/lib64:/usr/lib64/:usr/local/lib64"
			end
			path = path .. ":/lib:/usr/lib:/usr/local/lib"
		end
		
		if premake.libSearchPath then
			path = path .. delimiter .. table.concat(premake.libSearchPath, delimiter)
		end

		for _, fmt in ipairs(formats) do
			local name = string.format(fmt, libname)
			local result = os.pathsearch(name, path)
			if result then return result end
		end
	end


--
-- Scan the well-known system locations for a particular binary.
--

	function os.findbin(binname, hintPath)
		local formats = {} 
		local path = os.getenv("PATH") or ""
		
		if os.isfile(binname) then
			return os.getcwd()
		end
		
		if( hintPath ) then
			path = hintPath..os.getPathDelimiter()..path
		end
				
		local firstArg = string.find(binname, ' ')
		if firstArg then
			binname = string.sub(binname,1,firstArg-1)
		end

		-- assemble a search path, depending on the platform
		if os.is("windows") then
			formats = { "%s.exe", "%s.com", "%.bat", "%.cmd", "%s" }
		elseif os.is("haiku") then
			formats = { "%s" }
		else
			if os.is("macosx") then
				formats = { "%s", "%s.app" }
			else
				formats = { "%s" }
			end
		end

		for _, fmt in ipairs(formats) do
			local name = string.format(fmt, binname)
			local result = os.pathsearch(name, path)
			if result then return result end
		end
	end

--
-- Platform specific path delimiter
--
	function os.getPathDelimiter()
		if _OS == "windows" then 
			return ';'
		else 
			return ':' 
		end
	end

--
-- Retrieve the current operating system ID string.
--

	function os.get()
		return _OPTIONS.os or _OS
	end



--
-- Check the current operating system; may be set with the /os command line flag.
--

	function os.is(id)
		return (os.get():lower() == id:lower())
	end



--
-- Determine if the current system is running a 64-bit architecture
--

	local _64BitHostTypes = {
		"x86_64",
		"ia64",
		"amd64",
		"ppc64",
		"powerpc64",
		"sparc64"
	}
	local hostIs64bit 
	function os.is64bit()
		if( hostIs64bit == nil ) then
			-- Call the native code implementation. If this returns true then
			-- we're 64-bit, otherwise do more checking locally
			if (os._is64bit()) then
				return true
			end
			
			-- Identify the system
			local arch
			if _OS == "windows" then
				arch = os.getenv("PROCESSOR_ARCHITECTURE")
			elseif _OS == "macosx" then
				arch = os.outputof("echo $HOSTTYPE")
			else
				arch = os.outputof("uname -m")
			end
	
			-- Check our known 64-bit identifiers
			arch = arch:lower()
			for _, hosttype in ipairs(_64BitHostTypes) do
				if arch:find(hosttype) then
					hostIs64bit = true
					return true
				end
			end
			hostIs64bit = false
		end
		return hostIs64bit 
	end



--
-- The os.matchdirs() and os.matchfiles() functions
--

	function os.domatch(result, mask, wantfiles)
		local tmr = timer.start("os.domatch")
		-- need to remove extraneous path info from the mask to ensure a match
		-- against the paths returned by the OS. Haven't come up with a good
		-- way to do it yet, so will handle cases as they come up
		if mask:startswith("./") then
			mask = mask:sub(3)
		end
		
		-- if mask has double // from concatenating a dir with a trailing slash, remove it
		mask = mask:replace('//','/')
		
		-- recurse into subdirectories?
		local recurse = mask:find("**", nil, true)

		-- strip off any leading directory information to find out
		-- where the search should take place
		local basedir = mask
		basedir = path.getdirectory(basedir)
		if basedir:endswith("/**") then basedir = basedir:sub(1,#basedir-3) end
		basedir = basedir:replace("**","*")
		if (basedir == "." or basedir == "*") then basedir = "" end

		-- convert mask to a Lua pattern
		mask = path.wildcards(mask)

		local function matchwalker(basedir)
			if basedir:endswith("*") then
				local wildcard = basedir
				m = os.matchstart(wildcard)
				while (os.matchnext(m)) do
					if not os.matchisfile(m) then
						local dirname = os.matchname(m)
						matchwalker(path.join(basedir:sub(1,#basedir-1), dirname))
					end
				end
				os.matchdone(m)
				return
			end
			local wildcard = path.join(basedir, "*")

			-- retrieve files from OS and test against mask
			local m = os.matchstart(wildcard)
			local parentDir = iif( #basedir == 0, '', basedir..'/')
			while (os.matchnext(m)) do
				local isfile = os.matchisfile(m)
				if ((wantfiles and isfile) or (not wantfiles and not isfile)) then
					local fname = parentDir..os.matchname(m)
					if fname:match(mask) == fname then
						table.insert(result, fname)
					end
				end
			end
			os.matchdone(m)

			-- check subdirectories
			if recurse then
				m = os.matchstart(wildcard)
				while (os.matchnext(m)) do
					if not os.matchisfile(m) then
						local dirname = os.matchname(m)
						matchwalker(parentDir .. dirname)
					end
				end
				os.matchdone(m)
			end
		end

		matchwalker(basedir)
		timer.stop(tmr)
	end

	function os.matchdirs(...)
		local result = { }
		for _, mask in ipairs(arg) do
			os.domatch(result, mask, false)
		end
		return result
	end

	function os.matchfiles(...)
		local result = { }
		for _, mask in ipairs(arg) do
			os.domatch(result, mask, true)
		end
		return result
	end



--
-- An overload of the os.mkdir() function, which will create any missing
-- subdirectories along the path.
--

	local builtin_mkdir = os.mkdir
	function os.mkdir(p)
		if( _OPTIONS['dryrun'] ) then	
			printf("mkdir : " .. p .. '\n')
			return true
		end
			
		local dir = iif(p:startswith("/"), "/", "")
		for part in p:gmatch("[^/]+") do
			dir = dir .. part

			if (part ~= "" and not path.isabsolute(part) and not os.isdir(dir)) then
				local ok, err = builtin_mkdir(dir)
				if (not ok) then
					return nil, err
				end
			end

			dir = dir .. "/"
		end

		return true
	end


--
-- Run a shell command and return the output.
--

	function os.outputof(cmd)
		if _OPTIONS['dryrun'] then
			print( "Exec : "..cmd )
			return ""
		else
			local pipe = io.popen(cmd)
			local result = pipe:read('*a')
			pipe:close()
			if result:endswith('\n') then
				result = result:sub(1,#result-1)
			end
			return result
		end
	end


--
-- Remove a directory, along with any contained files or subdirectories.
--
	local removeList = {}		-- just so we don't print the same command twice

	local builtin_rmdir = os.rmdir
	function os.rmdir(p)
		if repoRoot then
			p = p:replace('$root/', repoRoot)
		end
		if( _OPTIONS['dryrun'] ) then
			if (os.isfile(p)	or os.isdir(p)) and (not removeList[p]) then
				print("rm -rf " .. p)
				removeList[p] = true
			end	
			return true
		end
		
		if os.readlink(p) == repoRoot then
			error("Can't delete repo root "..repoRoot)
		end
		
		if _OS == "windows" then
			os.execute("rmdir /s \""..p.."\"")
		else
			os.execute("rm -rf \""..p.."\"")
		end
	end

--
-- Remove a directory if it's empty, and any parents if they're empty too
--

	function os.rmdirParentsIfEmpty(p)
		p = path.getabsolute(p)
		if repoRoot then
			p = p:replace('$root/', repoRoot)
		end

		local dirs = os.matchdirs(p .. "/*")
		local files = os.matchfiles(p .. "/*")
		
		if (#dirs == 0) and (#files == 0) then
			
			if( _OPTIONS['dryrun'] ) then
				if not removeList[p] then	
					print("rmdir " .. p )
				end
				removeList[p] = true
			else
				builtin_rmdir(p)
			end
			
			local parent = path.getdirectory(p)
			os.rmdirParentsIfEmpty(parent)
			return true
		end
		return false
	end

	local builtin_remove = os.remove
	function os.remove(filename)
		if _OPTIONS['dryrun'] then
			print("rm -f "..filename)
		else
			return builtin_remove(filename)
		end
	end
	
	function os.createsymlink(sourceFile, linkTarget)
		if type(sourceFile) ~= 'string' or type(linkTarget) ~= 'string' then
			error("Expected string argument")
		end
		if _OS == "windows" then
			local cmd = "mklink "..sourceFile.." "..linkTarget
			os.execute(cmd)
		else
			local cmd = "ln -s "..sourceFile.." "..linkTarget
			os.execute(cmd)
		end			
	end
	
	function os.readlink(p)
		local linkTarget = os.getSymlinkTarget(p)
		if linkTarget then
			local pdir = path.getdirectory(p)
			local fullTarget = path.join(pdir, linkTarget)
			return os.readlink(fullTarget)
		end
		local name = path.getname(p)
		local parent = path.getdirectory(p)
		if parent ~= '/' and parent ~= p then
			return path.getabsolute(os.readlink(parent)..'/'..name)
		else
			return p
		end				
	end
	
	function os.copy(src, dest, onlyUpdate)
		if _OS == 'windows' then
			local cmd = iif(onlyUpdate, "xcopy /y /d ", "copy /Y ")
			cmd = cmd .. ' "'..src..'" "'..dest..'"'
			return os.execute(cmd)
		else
			if src:contains(":") or dest:contains(":") then
				local flags = iif(onlyUpdate, "-azqu", "-azq")
				local cmd = 'rsync '..flags..' "'..src..'" "' ..dest..'"'
				return os.execute(cmd)
			else
				local flags = iif(onlyUpdate, "-du", "-d")
				local cmd = 'cp '..flags..' "'..src..'" "' ..dest..'"'
				return os.execute(cmd)
			end
		end
	end
	
	function os.getfilesize(filename)
		local s = os.stat(filename)
		if not s then return nil end
		return s.size
	end
	
	local tempDirectory
	function os.tmpdir()
		if not tempDirectory then
			if _OS == 'windows' then 
				tempDirectory = path.join( os.getenv("TEMP"), os.getenv("USER") )
			else
				tempDirectory = path.join( "/tmp", os.getenv("USER") )
			end
			if not os.mkdir(tempDirectory) then
				error("Could not create temporary dir : ", tempDirectory)
			end
		end
		return tempDirectory
	end