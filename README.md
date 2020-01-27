# Speller
Spell checks a text file

1. Clone or download the repo to your machine.
2. ```cd``` to ```Speller/``` directory.
3. run ```make```
4. Assuming everything has gone right, run ```./speller```. It should tell you about correct usage.

## Note on using dictionary
##### ```./speller [DICTIONARY] text```
Now the optional argument to ```speller``` is a dictionary file. It's just another plain text file. Feel free to take a look inside the ```dictionaries/``` directory and see how the dictionary files are structured. If no argument is passed speller is going to use ```dictionaries/large``` by default. If you do pass any dictionary to speller explicitly, make sure that the ```dictionary``` passed to this program will be structured exactly like those in ```dictionaries/``` directory, alphabetically sorted from top to bottom with one word per line, each of which ends with ```\n```. You may also assume that dictionary will contain at least one word, that no word will be longer than ```LENGTH``` (a constant defined in ```dictionary.h```) characters, that no word will appear more than once, that each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe.
