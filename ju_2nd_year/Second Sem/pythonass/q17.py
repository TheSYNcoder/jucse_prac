import re

def decontracted(phrase):
    # specific
    phrase = re.sub(r"won\'t", "will not", phrase)
    phrase = re.sub(r"can\'t", "can not", phrase)

    # general
    phrase = re.sub(r"n\'t", " not", phrase)
    phrase = re.sub(r"\'re", " are", phrase)
    phrase = re.sub(r"\'s", " is", phrase)
    phrase = re.sub(r"\'d", " would", phrase)
    phrase = re.sub(r"\'ll", " will", phrase)
    phrase = re.sub(r"\'t", " not", phrase)
    phrase = re.sub(r"\'ve", " have", phrase)
    phrase = re.sub(r"\'m", " am", phrase)
    return phrase


def multi_to_single(phrase):
    phrase = re.sub(r"[\s]+" , " " , phrase)
    return phrase

def remove_special(phrase):
    phrase = re.sub(r"[^A-Za-z0-9\s]+" , "" , phrase)
    return phrase

def remove_single(phrase):
    phrase = re.sub(r"(^[a-zA-z]\s)|(\s[a-zA-z]\s)|(\s[a-zA-z]$)", " ", phrase)
    return phrase

def convert_lower(phrase):
    phrase = re.sub( r"[A-Z]" , lambda m : m.group().lower()  , phrase )
    return phrase

phrase = "hello long spaces        did it work?"
print(phrase , '\n :after removing mutiple spaces')
print( multi_to_single(phrase))
phrase ="A perfectly normal sentence  : oops ** omg ^(& let's clean it up "
print(phrase, '\n :after removing special characters')
print(multi_to_single(remove_special(phrase)))

phrase = "This sentence is going to be weird without a 'a' b s cd d"
print(phrase, '\n :after removing single characters')
print(remove_single(phrase))

phrase = "A phrase containing Upper and Lower CAses"
print(phrase, '\n :after converting into lower cases')
print(convert_lower(phrase))

phrase="I've always loved using decontracted words and i'll continue"
print(phrase, '\n :after decontracting')
print(decontracted(phrase))

'''
hello long spaces        did it work? 
 :after removing mutiple spaces
hello long spaces did it work?
A perfectly normal sentence  : oops ** omg ^(& let's clean it up  
 :after removing special characters
A perfectly normal sentence oops omg lets clean it up 
This sentence is going to be weird without a 'a' b s cd d 
 :after removing single characters
This sentence is going to be weird without 'a' s cd 
A phrase containing Upper and Lower CAses 
 :after converting into lower cases
a phrase containing upper and lower cases
I've always loved using decontracted words and i'll continue 
 :after decontracting
I have always loved using decontracted words and i will continue
'''
