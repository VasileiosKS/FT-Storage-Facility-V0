# FT-Warehouse-V0
<p align="center">
 <img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_Storage_Top-Down-1.jpg" style="width:80%; height:auto;">
</p>

# Video Demonstration

[<img src="https://github.com/VasileiosKS/FT-Storage-Facility-V0/blob/main/images/FT_Storage_Top-Down-2.jpg" width="600" height="300" />](https://youtu.be/TnXw6CiDf40)

# System Operation & GUI

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

# Issues enountered with V0
  - Power: No onboard voltage regulators were included, limiting the power that can be supplied on the 5V and 3.3V rails.
  - Footprint Error: An incorrect footprint was used for the TB6612FNG motor driver.
  - Connector & GPIOs: Not enough GPIOs were broken out, as a result permanent wires had to be soldered to the Pico.
    Additionaly the FT connector pads are spaced too tight.  
  - PCB Size: The PCB dimensions far exceeded the allowed dimensions, preventing it from fitting into its case.
  - I2C Issues: Certain pins belonging to non I2C devices were tied to I2C0 bus. Also could not get the AS5600 to work on I2C1 bus.
# Addresing issues of V0 in V1
To address the shortcomings of the prototype Version 0 (V0), several modifications were implemented in Version 1 (V1).
- Power Managment: The 5V and 3.3V power railes were reinforced by adding two AMS1117 LDO voltage regulators. Although these are considered obsolute with lower  effieciency compared to newer regulators, they were used due to existing stock.
- Motor Driver: The footprint error was corrected by replacing the TB6612FNG iwth the DRV8333. Decreased the number of module used by one, as well as the total amount of GPIOs needed. 
- Layout: Tight spacing issues were resolved. The number of broken-out GPIOs remains the same but changes to the pin assignments were made.
- Size Comparison:
  - V0 Dimensions: 68.453 mm x 57.150 mm aprox 3912.09 mm^2.
  - V1 Dimensions: 73.500 mm x 58.000 mm aprox 42563 mm^2.
  - Result in an area increase aprox 8.97 %.
  - The extra space was used to resolve previous clearance issues, while still staying within the safe margins of the 75 mm x 60 mm enclosure.
# Changes made in V2
 - Microcontroller: Went from RP2040 W to ESP32.
 - Component: From through-hole to surface mounted components.
 - Size: Reduced size.
# Commenting on V2
With this revision, i had a few goals in mind.
  1. Work on my soldering skills, especially get with surface mounted components (SMD).
  2. Schematic Design: Remember how to create schematics diagrams and use the editors.
  3. Custom Footprints: Design my own footprints.
  4. ESP32: Develop a custom pcb with an ESP32 module.
  5. PCB Routing: Route the entire PCB manually. in previous revisions, i had heavily relied on the auto-route function.
  6. PCB Manufacturing: Order the PCB with a stainless steel stencil to practice applying solder paste.

# Conclusion
Through this project, i successfully moved from through-hole components to SMD and used professional PCB manufacturing services to produce my custom designed. 
Many mistakes were made, which i learnt a lot from., while also realising that strategic compopnent placement is cruicial and greatly increased the efficience in routing. 
Overall, i am satisfied with the outcame of the project, since i aquired new knowledge and also practised my skills.

# Disclaimers
  - Usage of AI: Portions of the AS5600.h were generated by AI code generative tools, specifically the PI controller and position control implementetions.
  - All designs and information under this project, are open-sourced, and no monetary gains are expected.
  - This project is **not affiliated** with Fischer Technik or any of its trademarks.
  - This document was personally written and reviewed for syntactical errors using AI language tools.
    
# External Links
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
       (TBA)
