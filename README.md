# T-113-VLN1
## Group 3
### Instructor: Kristinn Þorri Þrastarson 
### Teacher: Daníel Brandur Sigurgeirsson
### Students: Bjartur Fannar Stefánsson, Björn Gunnarsson, Erla Björg Jensdóttir, Heiðar Berg Hallgrímsson, Védís Erna Eyjólfsdóttir
#### This program was created in a three-week course by 5 students, studying computer science in Reykjavík University, 2015.

#### 1. About the program
  * The program stores some facts about scientits that have contributed to computer science. The user can add new scientists, edit scientists that have already been added, retrieve the scientist's information and delete scientists.
  * Written in C++ language.

#### 2. How the program works
  * The program reads an input file and creates a list of scientists. It stores the scientist's name, age, sex, year of birth and year of death. The user can add new scientists to the file, edit scientists that are already in the file and remove scientists. The user can get a sorted results from the program. The program then saves all modifications to file.

#### 3. User instruction
> **Add new scientist to database**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *1. Add to the database*.
  3. Enter information about Scientist. Name, sex, year of birth and year of death. Year of death is 0 if scientist is still alive.
  4. The program outputs the information you have just entered. Press Y if you are satisfied and N if you want to change your input.
  5. New scientist has been added.

> **See scientists stored in database**
  1. After welcome message, choose *2. See database*.
  2. Choose wheather you want to see all scientists(1) or if you want to search by string/substring(2), birth year(3) or sex(4).
  3. Pick a way to sort your list. No sorting(1), sort by: name(2), year of birth(3), year of death(4) or sex(5). If you choose *1. No sorting*, jump to step 5.
  4. Choose wheather you want your output in an ascending(1) or descending(2) order.
  5. Your list will appear on the screen.

> **Search scientists by a string/substring**
  1. After welcome message, choose *2. See database*.
  2. Then choose *2. Search by a string or a substring*.
  3. Choose how you want your list to be sorted. No sorting(1), sort by: name(2), year of birth(3), year of death(4) or sex(5). If you choose *1. No sorting*, jump to step 5.
  4. Choose wheather you want your output in an ascending(1) or descending(2) order.
  5. Your list will appear on the screen.

> **Edit a scientist in database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *2. Edit an entry in the database*.
  3. Type in the name of the scientist you want to edit. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to edit.
  4. Choose what you want to change about that scientist. (1)Name, (2)sex, (3)year of birth, (4)year of death or (5)about.
  5. Type in the new information
  6. Check the updated information and press Y if you are done editing and N otherwise. If you press N, move back to 4. If you press Y, move to the next line.
  7. Scientist has been edited. 

> **Remove a scientist from database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *3. Delete an entry in the database*.
  3. Type in the name of the scientist you want to delete
  4. Type in the name of the scientist you want to delete. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to delete.
  5. Choose if you are sure wheather you want to delete the scientist or not.
  6. Scientist has been deleted.
