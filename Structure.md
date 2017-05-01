## General structure:

### DNA

| index        | Gene        | Range           | Affects  |
|---| ------------- |-------------| -----|
|0| Horizontal cost| 0/100 | A* |
|1| Verical cost | 0/100 | A*  |
|2| Atraction to gladiators| -100/100 | movement |
|3| Atraction to enemies| -100/100 | movement |
|4| Enemy detection radius | 0/1000 |movement |
|5| Gladiator detection radius | 0/1000 | movement |
|6| Attack radius | 0/100 | total attack|
|7| Attack| 0/100 | |
|8| Shield| 0/100 | total speed |
|9| Weight | 0/100 | total speed |


### Gladiator

| Attribute | type| Description|
|---|---|--|
|DNA|Integer array ||
|Identifier|string |MD5 hash based on it's DNA and creation time|
|Speed|float|calculated by it's DNA|
|Position|vector2f||
|Life|float||
|Fitness|float||


### Fitness calculation
Labyrinth fitness = ??
Colosseum fitness = (time alive)+(bonus * killed Gladiators)+(bonus * life)
Total fitness = Labyrinth fitness + Colosseum fitness

