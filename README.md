# rocket-league-staller

A quick and easy way to stall in Rocket League on a Windows PC.

### Disclaimer

This uses Rocket League's default keyboard binds to perform the stall, therefore if you've changed those binds in-game, you'll need to rebuild this after you've updated the [virtual-key codes](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes).

### How To Use

1. Run `Release/staller.exe`.
2. Press <kbd>Mouse Button 5</kbd> in-game!

If you want to close the program whilst in-game, press <kbd>END</kbd> on your keyboard.

### Changing Keyboard Binds

To change the key binds rocket-league-staller uses, navigate to `staller/staller.hpp`, then modify the entries in the `VirtualKeys` enum with the updated keys, then rebuild the project in Visual Studio Code.

For example, if you use <kbd>Space</kbd> to jump instead of <kbd>Mouse Button 2</kbd>, you'd want to change the `JUMP` entry in the `VirtualKeys` enum to `0x20` (The virtual key-code for <kbd>Space</kbd>).
