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
 **Add new scientist to database**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *1. Add a scientist to the database*.
  3. Enter information about Scientist. Name, sex, year of birth and year of death. Year of death is 0 if scientist is still alive.
  4. The program outputs the information you have just entered. Press Y if you are satisfied and N if you want to change your input.
  5. New scientist has been added.

 **Add new computer to the database**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *2. Add a computer to the database*.
  3. Enter information about Scientist. Name, year of build, type, about and wheather the computer was built or not. The computer types are electronic(1), mecanic(2), transistor(3) and other(4). If the user chooses 4, he has to enter the new type's name and the database will store it so it can be used again.
  4. The program outputs the information you have just entered. Press Y if you are satisfied and N if you want to change your input.
  5. New scientist has been added. 

 **See/Search scientists stored in database**
  1. After welcome message, choose *2. See database*.
  2. Now choose *1. Scientists*.
  3. Choose wheather you want to see all scientists(1) or if you want to search by name, full or partial(2), birth year(3) or sex(4).
  4. Pick a way to sort your list. Sort by: name(1), year of birth(2), year of death(3), sex(4) or no sorting at all(5). If you choose *5. No sorting*, jump to step 5.
  5. Choose wheather you want your output in an ascending(1) or descending(2) order.
  6. Your list will appear on the screen.

 **See/Search computers stored in database**
  1. After welcome message, choose *2. See database*.
  2. Now choose *2. Computers*.
  3. Choose wheather you want to see all computers(1) or if you want to search by name, full or partial(2), build year(3), type(4) or wheather it was built or not(5).
  4. Pick a way to sort your list. Sort by: name(1), year of build(2), type(3), wheather it was built or not(4) or no sorting at all(5). If you choose *5. No sorting*, jump to step 5.
  5. Choose wheather you want your output in an ascending(1) or descending(2) order.
  6. Your list will appear on the screen.

 **Edit a scientist in database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *4. Edit a scientist in the database*.
  3. Type in the whole name or a part of the name of the scientist you want to edit. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to edit.
  4. Choose what you want to change about that scientist. (1)Name, (2)sex, (3)year of birth, (4)year of death or (5)about.
  5. Type in the new information
  6. Check the updated information and press Y if you are done editing and N otherwise. If you press N, move back to 4. If you press Y, move to the next line.
  7. Scientist has been edited. 

 **Edit a computer in database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *5. Edit a computer in the database*.
  3. Type in the whole name or a part of the name of the computer you want to edit. If there are more than one computers in the database that match your input you will see a list of the matching computers and then you choose the ID of the computer you want to edit.
  4. Choose what you want to change about that computer. (1)Name, (2)build year, (3)type, (4)wheather it was built or not or (5)about.
  5. Type in the new information
  6. Check the updated information and press Y if you are done editing and N otherwise. If you press N, move back to 4. If you press Y, move to the next line.
  7. Computer has been edited. 

 **Remove a scientist from database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *6. Delete a scientist from the database*.
  3. Type in the name full name or a part of the name of the scientist you want to delete. If there are more than one scientists in the database that match your input you will see a list of the matching scientists and then you choose the ID of the scientist you want to delete.
  4. Choose if you are sure wheather you want to delete the scientist or not.
  5. Scientist has been deleted.

 **Remove a computer from database**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *7. Delete a computer from the database*.
  3. Type in the name full name or a part of the name of the computer you want to delete. If there are more than one computers in the database that match your input you will see a list of the matching computerss and then you choose the ID of the computer you want to delete.
  4. Choose if you are sure wheather you want to delete the computer or not.
  5. Computer has been deleted.

 **Add a scientist - computer relation**
  1. After welcome message, choose *1. Edit database*.
  2. Then choose *3. Add a scientist - computer relation*.
  3. Now add the scientist you want to connect by either searching for his name or press enter to see all scientists in database and choose the scientist's ID.
  4. Now add the computer you want to connect the scientist to by either searching for it's name or press enter to see all computers in database and choose the computer's ID.
  5. Scientist - computer relation has been made.

 **See a scientist - computer relation**
  1. After welcome message, choose *2. See database*.
  2. Choose wheather you want to see all scientists connected to a computer(3) or a computer connected to a scientist(4).
  3. Now look up the scientist/computer you want to see relations to by either typing the name or press enter to get a list of all computers/scientists and choose the computer's/scientist's ID.

 **Delete a scientist - computer relation**
  1. After welcome message, choose *1. Edit database*.
  2. Choose *8. Delete a scientist - computer relation*
  3. Now find the scientist of which you want to delete relations by either typing in his/her name or pressing enter to get a list of all scientists in database and then choose his/her ID.
  4. You will now see a list of all the computers this scientist is connected to and to delete relation, you simply choose the computer's ID of whom you wish to remove.
  5. Relation has been deleted.

#### 3. Programming rules
1. **Classes**
  * PascalCasing

2. **Variables**
  * camelCasing

3. **Functions**
  * camelCasing

4. **Comments**
  * Comments should be written above the code that is being explained as well as having the same indentation. The comments should always start with a space.

>    
**Not like this**

>      int object = number;
>      string thing = foo;  //Comment about the string
**But like this**

>      int object = number;

>      // Comment about the string
>      string thing = foo;
  
 * Comments about loops should not be "inside" the loop, but above it.

>    
**Not like this**

>      if(bool)
>      {
>        //Comment about the loop
>        foo = bar;
>      }
**But like this**

>      // Comment about the loop
>      if(bool)
>      {
>        foo = bar;
>      }

* Comments should be as short as possible, but concise. Should a comment too long to fit to the screen it should be divided to two or more lines.

>
**Like this**

>     // Lorem ipsum dolor sit amet, consectetur adipiscing elit, 
    //sed do eiusmod tempor incididunt ut labore et dolore magna  
    //aliqua. Ut enim ad minim veniam, quis nostrud exercitation  
    //ullamco laboris nisi ut aliquip ex ea commodo consequat.  
    //Duis aute irure dolor in reprehenderit in voluptate velit 
    //esse cillum dolore eu fugiat nulla pariatur. Excepteur sint
    //occaecat cupidatat non proident, sunt in culpa qui officia 
    //deserunt mollit anim id est laborum.

  * Comments on functions should be in Doxygen(/*!) and be placed **above** the function being explained.

5.**Curly brackets**
  
* Curly brackets should not open in the same line as a function name/loop condition except if it has only one shor line inside.

>    
**Not like this**

>      foo(){
     bar = i;
     i += i;
     }

> **But like this**
   
>      foo()
>      {
        bar = i;
        i += i;
>      }

> **The exception**
      
>      foo() { bar = i; }

6.**Loops and boolean conditions**
  
* Loops and boolean conditions should always have curly brackets

>     
**Like this**
      
>     if(bool)
    {
      foo = bar;
    }

>**But not like this**
     
>     if(bool)
        foo = bar; 

  * If a boolean condition is too long to fit in one line it should be broken down to two or more lines.

> 
**Not like this**
     
>       if(condition == anotherCondition && (something > somethingElse || something < theThirdThing))
      {
        foo = bar;
      }

> **But like this**
 
>       if(condition == anotherCondition
      && (something > somethingElse
      || something < theThirdTing))
     {
       foo = bar;
     }

7.**Lines and spacing**
  
* Try as mutch as possible to group similar things together, but if something is clearer in some other way the clarity wins.

* There should be a single empty line between "groups".

> 
**Not like this**

>     {
      int foo;
      string str;
      int numb;
      if(contidion){ bar = i; };
    }

> **But like this**
  
>     {
      int foo;
      int numb;
      string str;

>       if(contidion){bar = i; };
    }