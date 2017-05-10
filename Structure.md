## General structure:

### DNA

| index        | Gene        | Range           | Affects  |
|---| ------------- |-------------| -----|
|0| Horizontal cost| 0/100 | A* |
|1| Vertical cost | 0/100 | A*  |
|2| Diagonal cost | 0/100 | A*  |
|3| Atraction to gladiators| -100/100 | movement |
|4| Atraction to enemies| -100/100 | movement |
|5| Enemy detection radius | 0/1000 |movement |
|6| Gladiator detection radius | 0/1000 | movement |
|7| Attack radius | 0/100 | total attack|
|8| Attack| 0/100 | |
|9| Shield| 0/100 | total speed |
|10| Weight | 0/100 | total speed |


### Gladiator

| Attribute | type| Description|
|---|---|--|
|DNA|Integer array ||
|Identifier|string |MD5 hash based on it's DNA and creation time|
|Speed|float|calculated by it's DNA|
|Position|vector2f||
|Life|float| |
|Fitness|float|Calculated at the end of the cycle |


### Fitness calculation

Labyrinth fitness = Percentage completed + bonus for finishing

Colosseum fitness = (time alive)+(bonus * killed Gladiators)+(bonus * life)

Total fitness = Labyrinth fitness + Colosseum fitness
