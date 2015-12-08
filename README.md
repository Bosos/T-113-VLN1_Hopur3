# T-113-VLN1
## Group 3
### Instructor: Kristinn Þorri Þrastarson 
### Teacher: Daníel Brandur Sigurgeirsson
### Students: Bjartur Fannar Stefánsson, Björn Gunnarsson, Erla Björg Jensdóttir, Heiðar Berg Hallgrímsson, Védís Erna Eyjólfsdóttir
#### This program was created in a three-week course by 5 students, studying computer science in Reykjavík University, 2015.

#### 1. About the program
  * The program stores some facts about scientits that have contributed to computer science, celebrated computers from the history of computer science, and the relation between those two. The user can add, edit and delete scientists, computers and the relations between them, aswell as printing all those information to the screen in which order the user desires.
  * Written in C++ and SQL language.

#### 2. How the program works
  * The program is connected to a database in which it gets it's data from. The user can modify the database information(add, edit, delete information about scientists, computers and the relations between them) and the program updates the database "on the go". 

#### 3. User instruction
> **Add new scientist to database**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *1. Add a scientist to the database*.
  3. Enter information about Scientist. Name, sex, year of birth and year of death. Year of death is 0 if scientist is still alive.
  4. The program outputs the information you have just entered. Press Y if you are satisfied and N if you want to change your input.
  5. New scientist has been added.

> **Add new computer to the database**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *2. Add a computer to the database*.
  3. Enter information about Scientist. Name, year of build, type, about and wheather the computer was built or not. The computer types are electronic(1), mecanic(2), transistor(3) and other(4). If the user chooses 4, he has to enter the new type's name and the database will store it so it can be used again.
  4. The program outputs the information you have just entered. Press Y if you are satisfied and N if you want to change your input.
  5. New scientist has been added. 

> **See/Search scientists stored in database**
  1. After welcome message, choose *2. See database*.
  2. Now choose *1. Scientists*.
  3. Choose wheather you want to see all scientists(1) or if you want to search by name, full or partial(2), birth year(3) or sex(4).
  4. Pick a way to sort your list. Sort by: name(1), year of birth(2), year of death(3), sex(4) or no sorting at all(5). If you choose *5. No sorting*, jump to step 5.
  5. Choose wheather you want your output in an ascending(1) or descending(2) order.
  6. Your list will appear on the screen.

> **See/Search computers stored in database**
  1. After welcome message, choose *2. See database*.
  2. Now choose *2. Computers*.
  3. Choose wheather you want to see all computers(1) or if you want to search by name, full or partial(2), build year(3), type(4) or wheather it was built or not(5).
  4. Pick a way to sort your list. Sort by: name(1), year of build(2), type(3), wheather it was built or not(4) or no sorting at all(5). If you choose *5. No sorting*, jump to step 5.
  5. Choose wheather you want your output in an ascending(1) or descending(2) order.
  6. Your list will appear on the screen.

> **Edit a scientist in database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *4. Edit a scientist in the database*.
  3. Type in the whole name or a part of the name of the scientist you want to edit. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to edit.
  4. Choose what you want to change about that scientist. (1)Name, (2)sex, (3)year of birth, (4)year of death or (5)about.
  5. Type in the new information
  6. Check the updated information and press Y if you are done editing and N otherwise. If you press N, move back to 4. If you press Y, move to the next line.
  7. Scientist has been edited. 

> **Edit a computer in database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *5. Edit a computer in the database*.
  3. Type in the whole name or a part of the name of the computer you want to edit. If there are more than one computers in the database that match your input you will see a list of the matching computers and then you choose the ID of the computer you want to edit.
  4. Choose what you want to change about that computer. (1)Name, (2)build year, (3)type, (4)wheather it was built or not or (5)about.
  5. Type in the new information
  6. Check the updated information and press Y if you are done editing and N otherwise. If you press N, move back to 4. If you press Y, move to the next line.
  7. Computer has been edited. 

> **Remove a scientist from database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *6. Delete a scientist from the database*.
  3. Type in the name full name or a part of the name of the scientist you want to delete. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to delete.
  4. Choose if you are sure wheather you want to delete the scientist or not.
  5. Scientist has been deleted.

> **Remove a scientist from database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *7. Delete a computer from the database*.
  3. Type in the name full name or a part of the name of the computer you want to delete. If there are more than one computers in the database that match your input you will see a list of the matching computerss and then you choose the ID of the computer you want to delete.
  4. Choose if you are sure wheather you want to delete the computer or not.
  5. Computer has been deleted.

> **Add a scientist - computer relation**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *3. Add a scientist - computer relation*.
  3. //TODO

> **See a scientist - computer relation**
  //TODO

#### 3. Programming rules
  * blablabla
  * blablabla
  * //TODO