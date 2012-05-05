// Namespace Declaration
using System;

// Program start class
class WelcomeCSS
{
    // Main begins program execution.
    static void Main(string[] args)
    {
        int i;
		if (args.Length > 0)
		{
			Console.WriteLine("Loop Output: foreach (string name in args)");
			i = 0;
			foreach (string name in args)
			{
				Console.WriteLine("   arg {0}: {1}", i, name);
				i++;
			};
			Console.WriteLine("Loop Output: for(i = 0; i < args.Length; i++)");
			for(i = 0; i < args.Length; i++)
			{
				Console.WriteLine("   arg {0}: {1}", i, args[i]);
			};
			Console.WriteLine("Loop Output: while(i < args.Length)");
			i = 0;
			while(i < args.Length)
			{
				Console.WriteLine("   arg {0}: {1}", i, args[i]);
				i++;
			};
		} else {
			Console.WriteLine("Usage: loops <arg1> <arg2> ... <argX>");
        };
		return; 
    }
}