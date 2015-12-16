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

 1. Select the *Scientists*-tab.
 2. Fill out the name-, year of birth-, year of death- and about- fields, choose sex. About field can be left empty.
  * Birth can not be earlier than 1200 nor after 2015.
  * Death year can not be before birth.
  * Death can not be more than 120 years after birth.
  * Death year is left empty if scientist is still alive.
 3. Click Add-button.
 4. Scientist has been added and appears in list.

**Add new computer to the database**

  1. Select the *Computers*-tab.
  2. Fill out the name-, build year- and about- fields, choose type and wheather it was built or not. About field can be left empty.
      * Build year can not be before 1200 nor after 2015.
  3. Click Add-button.
  4. Computer has been added and appears in list.
  
**See/Search scientists stored in database**

  1. Select the *Scientists*-tab.
  2. Fill in the name/sex/birth year/death year/about you want to search by. Multiple fields can be filled to narrow search.
  3. Click the name of the column you want to arrange your search by. (Name, sex, birth, death, about)
 * To get the original order, press clear(Does not apply when adding relations in edit-mode)

**See/Search computers stored in database**

  1. Select the *Computers*-tab.
  2. Fill in the name/type/build year/was it built? you want to search by. Multiple fields can be filled to narrow search.
  3. Click the name of the column you want to arrange your search by. (Name, type, year, was it built?, about)
   * To get the original order, press clear(Does not apply when adding relations in edit-mode)

**Edit a scientist in database**

  1. Select the *Scientists*-tab.
  2. Search for the scientist you want to edit. (See *See/Search scientists stored in database*)
  3. Double-click the scientist you want to edit or choose the scientist and then press alt+E.
  4. Change the things you wanted to edit.
  5. Press the *Save* button or press alt+S.

* *(Scientists can be double-clicked in the list of scientists related to a computer, to edit.)*

**Edit a computer in database**

  1. Select the *Computers*-tab.
  2. Search for the computer you want to edit. (See *See/Search computers stored in database*)
  3. Double-click the computer you want to edit or choose the computer and then press alt+E.
  4. Change the things you wanted to edit
  5. Press the *Save* button or press alt+S

* *(Computers can be double-clicked in the list of computers related to a scientist, to edit.)*

**Remove a scientist from database**

  1. Select the *Scientists*-tab.
  2. Search for the scientist you want to delete. (See *See/Search scientists stored in database*)
  3. Double-click the scientist you want to edit or choose the scientists and the press alt+E.
  4. Press the *Delete* button or press alt+E.
  5. Confirm that you want to delete the scientist.
  6. Scientist has been deleted.

**Remove a computer from database**

  1. Select the *Computers*-tab.
  2. Search for the computer you want to delete. (See *See/Search computers stored in database*)
  3. Double-click the computer you want to edit or choose the computers and the press alt+E.
  4. Press the *Delete* button or press alt+E.
  5. Confirm that you want to delete the computer.
  6. Computer has been deleted.

**Add a scientist - computer relation**

  *There are two ways of doing this.*

  1. Select the *Scientist*-tab.
  2. Search for the scientist you want to delete. (See *See/Search scientists stored in database*)
  3. Double-click the scientist you want to edit or choose the scientists and the press alt+E.
  4. Press the *Add computers* button or press alt+A.
  5. Search for the computer you want to add the relation to. (See from step 2. in *See/Search computers stored in database*)
  6. Click the computer you want to add and then click the *Add selected* button or press alt+A.
  7. Relation has been added and appears in list
  
*Or*

  1. Select the *Computers*-tab.
  2. Search for the computer you want to delete. (See *See/Search computers stored in database*)
  3. Double-click the computer you want to edit or choose the computers and the press alt+E.
  4. Press the *Add scientists* button or press alt+A.
  5. Search for the scientist you want to add the relation to. (See from step 2. in *See/Search scientists stored in database*)
  6. Click the scientist you want to add and then click the *Add selected* button or press alt+A.
  7. Relation has been added and appears in list

**See a scientist - computer relation**

  *There are two ways of doing this.*

  1. Select the *Scientists*-tab.
  2. Search for the scientist you want to see relations to. (See *See/Search scientists stored in database*)
  3. Double-click the scientist you want to see relations to or choose the scientist and then press alt+E.
  4. Computers related to this scientist are shown in a list below edit section.

  *Or*

  1. Select the *Computers*-tab.
  2. Search for the computer you want to see relations to. (See *See/Search computers stored in database*)
  3. Double-click the computer you want to see relations to or choose the computer and then press alt+E.
  4. Scientists related to this computers are shown in a list below edit section.

**Delete a scientist - computer relation**
 
 *There are two ways of doing this*

 * *Delete computer from scientist*

  1. Select the *Scientists*-tab.
  2. Search for the scientist you want to delete relations to. (See *See/Search scientists stored in database*)
  3. Double-click the scientist you want to delete relations to or choose the scientist and then press alt+E.
  4. Computers related to this scientist are shown in a list below edit section. Choose the computer you want to remove from relations and click the *Remove selected computer* button or press alt+R.
  5. Relation has been deleted.
  
*Or*

 * *Delete scientist from computer*

  1. Select the *Computers*-tab.
  2. Search for the computer you want to delete relations to. (See *See/Search computers stored in database*)
  3. Double-click the computer you want to delete relations to or choose the computer and then press alt+E.
  4. Scientists related to this computer are shown in a list below edit section. Choose the scientist you want to remove from relations and click the *Remove selected scientist* button or press alt+R.
  5. Relation has been deleted.
  

#### 3. Programming rules
**1. Classes**
  * PascalCasing

**2. Variables**
  * camelCasing

**3. Functions**
  * camelCasing (except for functions made by QT, those are snake_cased

**4. Comments**
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

**5. Curly brackets**
  
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

**6. Loops and boolean conditions**
  
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

**7. Lines and spacing**
  
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

#### 4. Extra features
 
* **User can add a photo to computers and scientists**
* **Tables in edit window can be resizable.**
* **Computers and scientists can be deleted.(If a computer/scientist is deleted, it's relations and profile picture are deleted as well.**
* **Relations between computers and scientists can be deleted**
* **User gets error messages if he violates input constraints**
* **Shortcuts:**
  * alt+A - Add(search-mode)
  * alt+C - Cancel(edit-mode), Clear(search-mode)
  * alt+E - Delete(edit-mode), Edit(search-mode)
  * alt+P - Set profile picture(edit-mode)
  * alt+R - Remove(edit-mode)
  * alt+S - Save(edit-mode)