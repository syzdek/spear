// Namespace Declaration
using System;

// Program start class
class WelcomeCSS
{
    // Main begins program execution.
    static void Main(string[] args)
    {
		Console.Write("What is your name? ");
		string name = Console.ReadLine();
		Console.WriteLine("Hello {0}!\n\nGood bye!", name);
		return; 
    }
}