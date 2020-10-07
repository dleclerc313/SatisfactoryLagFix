This application will automatically fix the rubber-banding lag issue by modifying the .ini files in the user's AppData files.

Simply download and run FixSatisfactoryLag.exe to fix the issue.

It automatically follows the steps detailed on this wiki page: https://satisfactory.gamepedia.com/Multiplayer#Temporary_lag_solution and also described in this YouTube video: https://www.youtube.com/watch?v=0Di2C6MC2fI

It modifies the following three files:

C:\Users\<your_username_here>\AppData\Local\FactoryGame\Saved\Config\WindowsNoEditor\Engine.ini
C:\Users\<your_username_here>\AppData\Local\FactoryGame\Saved\Config\WindowsNoEditor\Game.ini
C:\Users\<your_username_here>\AppData\Local\FactoryGame\Saved\Config\WindowsNoEditor\Scalability.ini

These three files will be backed up when the program is run. If for some reason you run into issues, just replace these three files with the backup files.



-----------------------------------------------------------------------------------------------------------------------
Manual Instructions according to the Wiki Page (https://satisfactory.gamepedia.com/Multiplayer#Temporary_lag_solution
-----------------------------------------------------------------------------------------------------------------------

Temporary lag solution

There is a way to decrease rubber-banding at the cost of increasing bandwidth by adding the following lines to the game's config files found in %localappdata%\FactoryGame\Saved\Config\WindowsNoEditor\.[11] Before adding the lines to the config files, ensure they aren't already in place but with different values, if so, replace them instead of having duplicates.

By default, the game's maximum bandwidth appears to be throttled at 64 KB/s. By editing the config files, this limit is increased to about 100 MB/s.

This has to be done by all players (both the host and client/s) to have effect. The increased bandwidth can be even 5 times as much as it was before, therefore a stable internet connection is required.
Engine.ini

This file should be set as 'read only' to prevent the game from overwriting it.

[/Script/Engine.Player]
ConfiguredInternetSpeed=104857600
ConfiguredLanSpeed=104857600

[/Script/OnlineSubsystemUtils.IpNetDriver]
MaxClientRate=104857600
MaxInternetClientRate=104857600

[/Script/SocketSubsystemEpic.EpicNetDriver]
MaxClientRate=104857600
MaxInternetClientRate=104857600

Game.ini

This file should be set as 'read only' to prevent the game from overwriting it.

[/Script/Engine.GameNetworkManager]
TotalNetBandwidth=104857600
MaxDynamicBandwidth=104857600
MinDynamicBandwidth=10485760

Scalability.ini

This file will be initially blank and has to be set as 'read only' to prevent the game from overwriting it.

[NetworkQuality@3]
TotalNetBandwidth=104857600
MaxDynamicBandwidth=104857600
MinDynamicBandwidth=10485760


https://www.youtube.com/watch?v=46Ija2KKOXM
