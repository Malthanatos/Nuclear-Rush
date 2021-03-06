Nuclear Rush

Developed by:
Joseph Alvizo
Vincent Ha
Nathan Krueger
Shuntian Yao
Richie Poon

Code by:
Nathan Krueger


Rules / How to Play:

- Activate the Nuclear Rush.exe
	- Make sure that Puzzles.exe is in the same folder as Nuclear Rush.exe

- When you start the game it will open two windows:
	Reactor: shows the reactor, the cooling rod status, the time remaining until
		 the core overloads, and a password prompt*
	Puzzle: The current puzzle to solve and any hints you decide to activate

- Reactor:
	At any time (preferably before the core breaches) type in you guess for the password
	Pressing BACKSPACE will delete the entire password*
	Press HOME at any time to open the current puzzle window (in case you close it by accident)
		- Note that you can open multiple copies of a window if you want

- Puzzles:
	The puzzle will be printed in a second window
	Press enter for a hint
	If no more hints appear, there are none left to give
	The solution to the puzzle is the password for the current cooling rod
	All solutions will be fully lowecase to avoid confusion*

- You have until the timer runs out before the reactor explodes, killing everyone

- There are no consequences for using hints, but you should only use them if you need them

- While we have no way of enforcing this, you should not exit out of the reactor game in the
	middle of solving a puzzle.

- We do encourage, however, exiting the game after solving a puzzle if you want to take some
	time off to do something else (you can always restart the game and type the passwords
	you know). Note however that this will delete your current time/score.

- If you finish the game your total time/score is displayed

- If you lose the game... Well......

- Opening the Puzzles.exe file to get ahead of the game will not work, so don't bother

- The game is open source, so feel free to use/look at any code you see in the source files


*Notes from the developers*:
- Because of reasons (curse C++'s inability to read from the console while working...)
	typing and deleting from the password prompt is delayed by exactly 1 second.
	As a result you may (will almost certainly) notice a lag when you type.
	Do not try to compensate for this lag (or do, I'm just a few bytes of text not a cop),
	the game is picking up what you type it just isn't printing it out right away.

- Because of the above, BACKSPACE was made to delete the whole password line to prevent accidental
	deletions (since the passwords are not long this should not be an issue)

- Also because, for some reason, SHIFT and CAPS LOCK are considered "letters" and it is
	easier to assume all passwords are lowercase (to avoid confusion) than it is
	to write seperate conditions adding an integer value to an ASCII character to make
	it capitalized when SHIFT is pressed or when CAPS LOCK is on (also main is already
	too long and complicated and we do NOT need a reason to make it longer)