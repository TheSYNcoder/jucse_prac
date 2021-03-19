import random


def sanitize( e ):
	e = str(e)
	if len(e) <= 1:
		e = "0" + e
	return e

def gen_date():
	date = ""
	month = sanitize(random.randint( 1 , 12))
	day = sanitize( random.randint( 1, 27))
	year = "2021"
	return year +'-' + month +'-' + day


logos = open('links.txt' , 'r').read().split('\n')[:-1]
companies = open('names.txt' , 'r').read().split('\n')[:-1]
codes = open('codes.txt' , 'r').read().split('\n')[:-1]
dates = open('dates.txt' , 'r').read().split('\n')[:-1]
atime = open('atimes.txt' , 'r').read().split('\n')[:-1]
dtime = open('dtimes.txt' , 'r').read().split('\n')[:-1]
acity = open('acities.txt' , 'r').read().split('\n')[:-1]
dcity = open('dcities.txt' , 'r').read().split('\n')[:-1]
price = open('prices.txt' , 'r').read().split('\n')[:-1]
legs = [ random.randint(1,4) for _ in range(106) ]
with open('comb.txt' , 'w') as f:
	for i ,obj in enumerate(zip(logos, companies, codes, dates, atime, dtime, acity, dcity, price ,legs)):
		s = str(i) +','+ ','.join( str(o) for o in obj)
		f.write(s +'\n')
	 


	
