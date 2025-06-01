# Galactic Star Wars Battleship Game

**Overview** 
Galactic NCC Star Wars Battleship is a console-based C++ game inspired by classic Battleship, set in a Star Wars–themed galaxy. Two players (Rebel and Imperial commanders) take turns placing fleets on a grid and attempting to sink each other’s ships.

**Language Used**  
- C++17



## Game Rules

1. **Battle Modes & Grid Sizes**  
   - **The Swiftstrike**: 5×8 grid  
   - **The Starlight Clash**: 8×10 grid  
   - **Wrath of Titans**: 10×12 grid  

2. **Fleet Composition**  
   | Ship Class               | Grid Size (Cells) | Hits to Destroy | Laser Bursts per Turn |
   |--------------------------|-------------------|-----------------|-----------------------|
   | Star Destroyer           | 5                 | 4               | 3                     |
   | Mon Calamari Cruiser     | 4                 | 3               | 4                     |
   | X-Wing Squadron          | 3                 | 2               | 2                     |
   | TIE Fighter              | 1                 | 1               | 1                     |

   - **Placement**: Each ship occupies contiguous cells horizontally, vertically, or diagonally.  
   - Ships cannot overlap or extend beyond the grid.

3. **Hit & Sink Mechanics**  
   - A ship is “hit” when a shot coordinates match one of its cells.  
   - If a ship receives its required number of hits (Hits to Destroy), it is “sunk” and all its cells become visible.  


4. **Dice Effect (Special Bonus)**  
   - If a player scores **at least 2 hits in a single turn**, a random “dice effect” is triggered (1–100 roll):  
     1. **1–10 (10%)**: Add a new ship to your fleet (random type)—if no valid space remains, skip.  
     2. **11–40 (30%)**: Gain **one extra shot** this turn.  
     3. **41–60 (20%)**: Opponent’s next turn shot count is **reduced by one**.  
     4. **61–80 (20%)**: Opponent is limited to **only 1 shot** on their next turn.  
     5. **81–100 (20%)**: Gain **an extra entire turn** immediately after this one.

5. **Win Condition**  
   - The first player to sink all enemy ships wins immediately.
