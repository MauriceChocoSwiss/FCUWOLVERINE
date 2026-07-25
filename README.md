# FCUWOLVERINE
A FCU for Wolverine airsoft HPA system

---

## Small Presentation of the project

It's an custom hand made fcu based on arduino nano. i've some options like marg switch and charging Handle connection.
In addition to standards mode like semi, burst and full auto, a sniper mode is available. Unfortunately, no shotgun mode due to lack of nozzle poppet solenoid

---

## Basic features & specs 
- Only lipo 2S compatibility -- Voltage control and warning, block firing if battery is too low -> see menu settings to find options relative to battery voltage
- Dwel and rof setting. Dwel is common for all mode and ROF for burst and full auto mode.
- Sniper mode with adjustable delay
- Magazin settings -- Max bb's per mag settings, blocking fire when "mag is empty", alarm "near to empty", charging handle to reset mag capacity, mag switch to prevent blank fire

For more details about options and features, see menus below ;)

---

Menu list by order

NOTA: 0 is for no or false and 1 for yes or true

### Main menu (if not in programming mode)-> 

  - Top Left: theorical bb's remaining in the mag and theorical bb's amount in the mag
  
  - Top Right: total bb's shoot since powered up
  
  - Bottom Left: Firing mode. For the burst, burst quantity displayed
  
  - Bottom Right: battery voltage

### Programing menus (navigate with up and down)

### Burst /Full auto Menu -> 

  - Top Left: Rate of fire in Full auto
  
  - Top Right: Rate of fire in Burst
  
  - Bottom Left: Burst bb quantity

### Sniper Menu ->

  - Top left: Activating green LED for "Ready to shoot" signal
  
  - Bottom left: Delay to simulate sniper mode (can't soot during pause)
  
### Mag Menu -> 

  - Top Left: Theorical bb's count in mag (can be less than real capacity)
  
  - Top Right: Activating blocking when bb's count left equal 0
  
  - Bottom Left: Activating mag detection (via wired binary switch). If ON, the fcu will fire only if a the mag switch is actived. If OFF, the FCU will work anytime
  
  - Bottom Right: Activating of "Mag almost empty" buzzer

### Mag Menu 2 -> 
  
  - Top Left: Activation of "Mag almost empty" and "Empty mag" alarm LED's
  
  - Bottom Right: BB's amount for "Mag almost empty".
  
  - Bottom Left: Activation of the charging handle / If ON + empty mag blocking ON, if you change the mag you need th cook to be able to shoot
  
  - Bottom Right: Charging handle LED, meaning "Ready to shoot"

### Settings Menu -> 
Values details for selector
  1: Semi
  2: Burst
  3: Full
  4: Sniper
  
  - Top Left: Selector on SEMI shooting mode

  - Top Right: Voltage alarm with shoot blocking 
  
  - Bottom Left : Selector FULL auto shooting mode
  
  - Bottom Right: Dwel settings, max 200, increase by 1
