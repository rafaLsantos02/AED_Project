This project was developed during the curricular unit AED (Algorithms and Data Structures), in collaboration with a college colleague (@gfirme). 
The main goal of this project was to create a program in C capable of finding the path of minimum cost between two words of the same length, where each word in the path is obtained from the previous one by mutating one or more characters, while ensuring all intermediate words belong to a given dictionary.

The application had several key functionalities, such as:
  1. Reading input files:
  2. A dictionary file (.dict) containing all possible words.
  3. A problem file (.pals) containing pairs of words and the maximum number of characters allowed to change per mutation.
  4. Producing an output file (.paths) listing the sequence of words that form the lowest-cost transformation path between each pair of words (or indicating when no solution exists).
  5. Handling invalid input gracefully, such as missing files, wrong extensions, or invalid problems.
  6. Ensuring robust file parsing, supporting dictionaries with mixed formatting (spaces, tabs, or multiple words per line).
  7. Ensuring efficient performance regarding execution time and memory usage, given the automatic evaluation environment.

In the folder Mix01, I included several examples showing how the .pals files must be written, as well as the corresponding solution files (.paths) for each .pals file in the folder.
I also added the **.dict** file used by the application, since this program only supports dictionaries composed exclusively of words made up of **unaccented Latin characters** and **without hyphens or special symbols** (such as punctuation marks or other non-alphabetic characters).
These files serve both as test cases and demonstrations of how the application processes input and produces output, illustrating the expected format and behavior of the program.
