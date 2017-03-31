using CppSharp.AST;
using CppSharp.Generators;
using CppSharp.Passes;

namespace CppSharp
{
    class HeliosBinder : ILibrary
    {
        /// Setup the driver options here.
        public void Setup(Driver driver)
        {
            var options = driver.Options;
            options.GeneratorKind = GeneratorKind.CSharp;
            var module = options.AddModule("Sample");
            module.Headers.Add("Sample.h");
            module.Libraries.Add("Sample.lib");
        }

        /// Setup your passes here.
        public void SetupPasses(Driver driver)
        {
            driver.Context.TranslationUnitPasses.RenameDeclsUpperCase(RenameTargets.Any);
            driver.Context.TranslationUnitPasses.AddPass(new FunctionToInstanceMethodPass());
        }

        /// Do transformations that should happen before passes are processed.
        public void Preprocess(Driver driver, ASTContext ctx)
        {

        }

        /// Do transformations that should happen after passes are processed.
        public void Postprocess(Driver driver, ASTContext ctx)
        {

        }

        static class Program
        {
            public static void Main(string[] args)
            {
                ConsoleDriver.Run(new HeliosBinder());
            }
        }
    }
}