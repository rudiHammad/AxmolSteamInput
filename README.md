# AxmolSteamInput

# 1. install the sdk
For this you have to register in steamworks https://partner.steamgames.com/. From there you download the last sdk. 

# 2. Setup visual studio
Copy the folder steamworks to the path you want and then  depending on what idle and OS you are using, you have to set the paths to include the libraries.
(steamworks contains sdk directory, wich contains other directories aswell. You should set the path to the public folder. 
For instance, for windows and visual studio:
C++ | General | Additional include directories, add pathTo\steamworks\sdk\public
Linker | Input| Additional Dependencies, add pathTo\steamworks\sdk\redistributable_bin\win64\steam_api64.lib

# 3. steam_api64.dll and steam_appid.txt
Copy the team_api64.dll and steam_appid.txt in the output directory(where the executable is after the build). For instance copy steam_api64.dll in the Debug or Release folder.
The content of steam_appid.tx is the id of your app (meaning game) that is provided by steam when you become a steam partner (100$ per game). But you can you downlaod Spacewar which
is a free app with id 480 used for testing. So the content od steam_appid.txt in that case is 480.

![steam_tutorial_1](https://github.com/user-attachments/assets/fd6308e9-d3dd-45ee-9b84-d924eb740084)


(copy those files also in realease)

# 4. Create the vdf file
In you library search you app, in this case Spacewar, right-click |the game mange | controller layout. This will lead you to this interface
![inputMenu](https://github.com/user-attachments/assets/e3957776-1c0e-41ea-869a-291549ac046f)

Here you can create the layout that maps each button, pad, etc.. to an action. You can find more info here https://www.youtube.com/watch?v=7I4SiAiKqqk&t=2538s,
but in a nutt shell once you do the layout, you can export it, and it will create the vdf file int the following directory:
![steamVDB](https://github.com/user-attachments/assets/d4c0d750-e518-41e8-aa33-263da97854ef)


At this point steam should be integrated with axmol. So now you can use the steam api to use SteamInput, Steam leadboards, etc...

In the source code added you can find the very basics to test it. The code is a bit messy but the goal is simply to trigger a message
when the x button is pressed.

# Important consideration
1. you should have steam openned
2. you probaly want to disable steam input when you are in you desktop. For this go to big picture mode | setting | controller | Desktop Layour | edit | disable steam input 
3. you should make sure that you have applied the layout

![Capture](https://github.com/user-attachments/assets/9b680390-4916-4d23-87e7-b551e2a93dcc)


# Finicky stuff
1. Currently you need to click outside with the mouse ourside the viewport, and then click back in it, otherwise it won't trigger the inputs...
 could be related to steam big picture mode? 
