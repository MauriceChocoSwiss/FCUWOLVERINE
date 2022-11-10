# FCUWOLVERINE
A FCU for Wolverine airsoft HPA system

---

## Small Presentation of the project

It's an custom hand made fcu based on arduino nano. i've some options like marg switch and charging Handle connection.
In addition to standards mode like semi, burst and full auto, a sniper mode is available. Unfortunately, no shotgun mode due to lack of nozzle poppet solenoid

---

For the switch, use something like this : https://aliexpress.com/item/32847441181.html?spm=a2g0o.order_list.0.0.8b0b5e5brNzxPX&gatewayAdapt=glo2fra

And a screen like this : https://aliexpress.com/item/32815893431.html?spm=a2g0o.order_list.0.0.8b0b5e5brNzxPX&gatewayAdapt=glo2fra

---

## Basic features & specs 
- Only lipo 2S compatibility -- Voltage control and warning, block firing if battery is too low -> see menu settings to find options relative to battery voltage
- Dwel and rof setting. Dwel is common for all mode and ROF for burst and full auto mode.
- Sniper mode with adjustable delay
- Magazin settings -- Max bb's per mag settings, blocking fire when "empty mag", alarm "near to empty", charging handle to reset mag capacity, mag switch to prevent blank fire

For more details about options and features, see menus below ;)

---

Menu list by order

NOTA: 0 is for no or false and 1 for yes or true

### Main menu -> 

  - Top Left: theorical bb's remaining in the mag and theorical bb's amount in the mag
  
  - Top Right: total bb's shoot since powered up
  
  - Bottom Left: Firing mode. For the burst, the ammount is the burst quantity
  
  - Bottom Right: Tension de la batterie

### For the next menus, i'll explain them when you go UP

### Burst /Full auto Menu -> 

  - Top Left: Rate of fire in full auto
  
  - Top Right: Rate of fire in Burst mode
  
  - Bottom Left: Burst bb count

### Sniper Menu ->

  - Top left: Activating green LED for "Ready to shoot" signal
  
  - Bottom left: Delay to simulate sniper mode
  
### Mag Menu -> 

  - Top Left: Theorical bb's count in mag (can be less than real capacity)
  
  - Top Right: Activating blocking when bb's count fall to 0
  
  - Bottom Left: Activating mag detection (via wired switch). If ON, the fcu will fire only if a the mag switch is pushed. If OFF, the FCU will work anytime
  
  - Bottom Right: Activating of "Low capacity" buzzer

### Mag Menu 2 -> 
  
  - Top Left: Activating of "low capacity" and "Empty mag" alarm (only LED's)
  
  - Bottom Right: BB's amount for "Low capacity".
  
  - Bottom Left: Activating of the charging handle/ If ON + empty mag blocking ON, if you change the mag without manipulate the charging handle, you can't fire
  
  - Bottom Right: Charging handle LED, meaning "Ready to shoot"

### Settings Menu -> 
  
  - Top Left: Screen locking -> unlocking delay : 3 Sec
  
  - Top Right: Screen off delay 30sec by 30sec
  
  - Bottom Left: Voltage alarm with shoot blocking 
  
### Settings Menu 2 ->

Values details for selector
  1: Semi
  2: Burst
  3: Full
  4: Sniper
  
  - Top Left: Selector on SEMI shooting mode
  
  - Bottom Left : Selector FULL auto shooting mode
  
  - Bottom Right: Dwel settings, max 200, increase by 1
