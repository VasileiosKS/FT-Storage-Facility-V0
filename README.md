# FT-Warehouse-V0
<p align="center">
 <img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_Storage_Top-Down-1.jpg" style="width:80%; height:auto;">
</p>

# Description

- 

# Video Demonstration

[<img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_Storage_Top-Down-2.jpg" width="600" height="300" />](https://youtu.be/TnXw6CiDf40)

# System Operation & GUI:

Unlike the [Color Sorting Station](https://github.com/VasileiosKS/FT-Colour-Sorting-Station-V0), which operated (somewhat) autonomously using infrared and color sensors to detect and sort objects, this system is command-based. It executes specific tasks upon receiving serial commands.

# Functions:

 1. **RETRIEVE AN OBJECT:** The whole carriage moves to a specific shelf slot to pick up an object.
    ```
    Command: RETRIEVE X (where X is the slot number).
    ```
2. **STORE AN OBJECT:** Once again the whole carriage moves to a designated slot place an object into the shelf.
   ```
   Command: STORE X (where X is the slot number).
   ```
3. **MANUAL CONTROL:**
   Beyond the main two functions, the system allows for manual control of individual subsystems and mechanisms, including:
    - Operating the Gripper: Manually adjusting the servo angle.
    - Moving the platform.
    - Raising or lowering the arm at specified points.
    - Extending or retracting the arm.
      
# GUI
While sending commands via a terminal is functional, it gets old real fast. To improve the user experience, i decided to develop a dedicated GUI.
Initially, i attempted to build a custom interface using Python (Tkinter and Serial libraries), but failed miserably due to my inexperience with Python. Will attempt again at a later point. 
Out of curiocity, i expermiented with gen AI to produce the code based on what i had in mind. The result aligned with what i had in mind, however i chose not to use the AI-generated.
Ultimately, i went for Node-Red, a tool i am familiar with. Using the nodes mentioned below, i created a simple UI shown below. With just a few clicks, the user can easily perform the "STORE", "RETRIEVE" and the manual operations mentioned previously.

 - Node-Red
    - Flow
      <p align="center">
        <img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/nodered-flow.PNG" alt="Alt Text" style="width:50%; height:auto;">
      </p> 
    - GUI
      <p align="center">
        <img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/nodered-ui.PNG" alt="Alt Text" style="width:50%; height:auto;">  
      </p>
  - Nodes Used:
       ```
       - node-red-contrib-pythonshell
       - node-red-contrib-ui-joystick
       - node-red-contrib-ui-led
       - node-red-contrib-ui-dashboard
       - node-red-node-serialport
       - node-red-contrib-ui-iframe
       ```

# PCB Design: Version 0

PCB Schematics             |  PCB 3D Rendering         | Assembled PCB
:-------------------------:|:-------------------------:|:-------------------------:
![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V0_Schematics.PNG)  |  ![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V0_PCB_CAD.PNG) | <img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V0_PCB.jpg" alt="Alt Text" style="width:80%; height:auto;"> 

# PCB Design: Version 1

PCB Schematics             |  PCB 3D Rendering         |
:-------------------------:|:-------------------------:|
![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V1_Schematics.PNG)  |  ![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V1_PCB_CAD.PNG) | 

# PCB Design: Version 2 (Final Version)

Rather than using through-hole components that consume excessive space, this final iteration adopts surface-mount components to achieve a more compact design. Also, i recently aquired a hot air station making it a bit easier to work with those tiny components.

PCB Schematics             |  PCB 3D Rendering         | Assembled PCB
:-------------------------:|:-------------------------:|:-------------------------:
![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V2_Schematics.PNG)  |  ![](https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_RP2040_V2_PCB_CAD.PNG) | 


# Overview:
Although this was the first PCB i designed and manufactured, its functional though not without its challenges. Most of the issues encountered are detailed below.

# Issues enountered with V0:  
  - Power: No onboard voltage regulators were included, limiting the power that can be supplied on the 5V and 3.3V rails.
  - Footprint Error: An incorrect footprint was used for the TB6612FNG motor driver.
  - Connector & GPIOs: Not enough GPIOs were broken out, as a result permanent wires had to be soldered to the Pico.
    Additionaly the FT connector pads are spaced too tight.  
  - PCB Size: The PCB dimensions far exceeded the allowed dimensions, preventing it from fitting into its case.
  - I2C Issues: Certain pins belonging to non I2C devices were tied to I2C0 bus. Also could not get the AS5600 to work on I2C1 bus.
# Addresing issues of V0 in V1:
 -
 -
 -

# Disclaimers:
  - Usage of AI: Portions of the AS5600.h were generated by AI code generative tools, specifically the PI controller and position control implementetions.
  - All designs and information under this project, are open-sourced, and no monetary gains are expected.
  - This project is **not affiliated** with Fischer Technik or any of its trademarks.
  - This document was personally written and reviewed for syntactical errors using AI language tools.
    
# External Links:
   - 3D Parts:
     - Made by other designers: 
       - Gripper:
           - Made by user: PHabermehl
           - Link: https://www.thingiverse.com/thing:3419079
       - AS5600 Holder:
           - Made by user: juh
           - Link: https://www.printables.com/model/858685-fischertechnik-i2c-as5600-white-pcb-contactless-ro
       - Hall Effect Sensor holder:
           - Made by user: juh
           - Link: https://www.printables.com/model/356060-hall-sensor-for-fischertechnik
       - Worm nut:
           - Made by user: psterk
           - Link: https://www.thingiverse.com/thing:4596745
       - Worm screw:
           - Made by user: thomasdr
           - Link: https://www.thingiverse.com/thing:2156787 
     - Made by me:

