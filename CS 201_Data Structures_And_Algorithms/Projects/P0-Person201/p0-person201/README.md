# Project 0: Person201

## Obtaining Project Code and Project Details

For details and FAQs, see [this document](docs/details.md) that has information on git, Java, the classes here, and more. This current file you're reading has project and coding details, but the linked document has more Java and git details, particularly about starting to code. That linked document includes information about project workflow including submitting code and analysis for grading via _Gradescope_. *Be sure to check [this document](https://coursework.cs.duke.edu/cs-201-spring-24/resources-201/-/blob/main/projectWorkflow.md) for how to use Git to obtain the project files, and workarounds if Git doesn't work yet for you. You'll need to refer to this P0 document when forking and cloning.

## Recording on Zoom
For this project and every APT quiz, you will record your screen via Zoom. For APT quizzes, you will record for the full duration of the quiz, but for this project, you will only record the first 20 minutes when you start coding -- not when you start reading, but when you're ready to code. You'll submit a URL for a cloud Zoom recording [using this link](https://duke.is/y/yfcv).

## Goals

* To modify a simple Java class, modify two driver programs, and create a new class to demonstrate understanding of classes, methods, and instance variables.
* To learn about running Java programs using the VSCode IDE
* To learn about using Git for project management.
* To learn about CompSci201 workflow for assignments: Git, Gradescope, helper hours.


## Developing the classes in Project P0: Person201

When you fork and clone the project, you'll be working primarily within the src folder with .java files beginning with `Person201`. Your goal is to modify three programs/classes (`Person201.java`, `Person201Demo.java`, and `Person201NearbyDemo.java`) and create a new program (`Person201Closest.java`) to generate the desired output. 


### Run `Person201Demo.java` and change `Person201.java`

First run the main method in `Person201Demo.java`, the output will be:

```
037.80N,122.27W claire courons
001.29S,036.82E ricardo harambee
040.71N,073.96W julie help
000.00N,000.00E null null
names: claire ricardo julie null 
```

Make changes to `Person201.java` by modifying the default constructor so the output will be as shown. Use the comments for the constructor 
to help understand how to do this, see the [help-doc/FAQ](docs/details.md) for more details.

```
037.80N,122.27W claire courons
001.29S,036.82E ricardo harambee
040.71N,073.96W julie help
035.93N,079.01W Owen woto
names: claire ricardo julie Owen
```

Now that you've done this, change the `main` method in file `Person201Demo.java` by creating a new `Person201` variable named `s` (short for Sam) as follows:

`Person201 s = new Person201("Sam", 44.9978, -93.2650, "hello");`

Next, change the definition of the array `people` to include `s` such that `s` appears between `r` and `j`. Then run the program. The
output should be as shown here:

```
037.80N,122.27W claire courons
001.29S,036.82E ricardo harambee
045.00N,093.27W Sam hello
040.71N,073.96W julie help
035.93N,079.01W Owen woto
names: claire ricardo Sam julie Owen 
```

### Running Person201NearbyDemo, Modify Person201.java, and changing Data Source

Run the program `Person201NearbyDemo`. It reads a data file and finds all the people in the data file who are within 50 miles of a person named Ricardo who lives near Seattle. The program prints there are no people because the method `Person201.distanceFrom` returns the value _100_ instead of the correct distance to the parameter `other`. Modify the body of `Person201.distanceFrom` so that it calls
`Person201Utilities.distance` and passes the correct parameters to get the distance between `this` object and the parameter `other`. Then rerun
`Person201NearbyDemo` -- you should see data from 16 people who are within 50 miles of Ricardo.

Lines 20-22 specify three data sources: a regular text file named `large` in the `data` folder, an encrypted file in the same `data` folder (line 21), and an encrypted URL (line 22). Verify by commenting out/uncommenting each line that those sources all produce the same results, e.g., 16 people within 50 miles of Ricardo. After verifying the results are the same, write a new line that reads data from the URL specified by the
variable `largeURL`. You'll need to call the appropriate method in `Person201Utilities` to read a URL for a plain-text file. Verify that you get the same results since that URL references the same data as the file `large` in the `data` folder. You'll answer questions about these
runs in the Analysis section. 


### Create and Run a New Java Class: **Person201Closest**

In the `src` folder create a new Java class named `Person201Closest` (name the file `Person201Closest.java`) that has only a `public static void main method` that allows the program to run. When run, the method should read the file `large.txt` in the `data` folder and determine the two distinct (i.e., inequal) `Person201` objects that are the closest together. You may find the code in `Person201NearbyDemo.java` useful in reasoning about the code you write. The program should print the two distinct objects that are closest together among all the objects created and returned when `PersonUtilities.readFile` is called from the code you write.

The `main` method you write *must* use the code below 
```
public static void main(String[] args) throws Exception {
        String file = "data/large.txt";
        double min = Double.MAX_VALUE;
        Person201 a = null;
        Person201 b = null;
        // TODO: finish this method 
        System.out.printf("closest distance is %3.2f between %s and %s\n",min,a.getName(),b.getName());
    }
```

## Checklist

Before you submit to Gradescope, check that you've done each of the following:

- Modify `Person201.java` by changing code in two places.
- Verify that running `Person201Demo.java` matches the expected output after modifying `Person201.java`
- Add a new `Person201` object in the `Person201Demo.java` program and verify that running `Person201Demo.java` matches the expected output.
- Run `Person201NearbyDemo.java` after modifying the method `distanceFrom` in  `Person201`, and verify the results hold reading the same data 
four different ways: a text file, an encrypted text file, and the same via URLs.
- Create a new class `Person201Closest` (in a new file named accordingly) with a `main` method to find the two distinct (i.e., inequal) people closest to each other.

## Submission

You'll submit by pushing your code to Git and using Gradescope. Details can be found in [the details/FAQ](docs/details.md).

## Analysis

Answer all the questions here. As outlined in [this document](docs/details.md) you'll submit a PDF with your answers to Gradescope.

### Question 1
- How many instance variables are there in `Person201`?
- How many constructors are there in `Person201`?

### Question 2
- Does the main method of your `Person201Closest.java` create any objects of type `Person201Utilities`? Why or why not?

### Question 3
According to the `.equals` method of the `Person201` class, when are two `Person201` objects considered to be equal? Is it case sensitive for their names or for their phrases? (Case sensitive means different answers are returned depending on capitalization).

### Question 4
The online data for this project read via URL is encrypted. In a few sentences, why is it reasonable to have the online data encrypted?

### Question 5
Read/skim [this description of AES](https://techjury.net/blog/what-is-aes/), the encryption algorithm used in this project, e.g., see the code in `FileEncryptor.java`. What are two things you learned from this article that you think are relevant to your understanding of Computer Science?

### Question 6
As stated at the start of this document and in the course policies, you should record via Zoom the first 20 minutes of you working at the beginning of this project and submit a link to that recording using [this form](https://duke.is/y/yfcv). In your analysis document, include as an answer to Question 6 an affirmation "Yes, I submitted the URL for a Zoom recording." -- if, in fact, you did.

## Grading

Your submission will be graded by the following chart:

| Project Part | Points |
| ------ | ------ |
| Modify Person201 | 6 |
| Modify Person201Demo | 6 |
| Create Person201Closest | 6 |
| Zoom recording | 2 |
| Analysis | 5 |
