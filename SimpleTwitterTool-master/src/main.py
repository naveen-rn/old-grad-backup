import globals
import developer_details
import login
import tweet
import help
import stream
from sys import *

globals.init()
developer_details.initialize()
login.verify_login()

if len(argv) <= 1 or len(argv) > 2:
	print "Welcome MiniTweet"
	print "Use some options and restart the program: \
		   \n1 -> help \
		   \n2 -> tweet \
		   \n3 -> view previous tweet \
		   \n4 -> view tweets from people you follow"
	exit()

avail_functions = [1, 2, 3, 4]

if int(argv[1]) in avail_functions:
	tweet.tweet_hello()
	if int(argv[1]) == 1:
		help.help_statement()
	elif int(argv[1]) == 2:
		tweet.tweet_post(tweet.tweet_get())
	elif int(argv[1]) == 3:
		stream.previous_tweet()
	elif int(argv[1]) == 4:
		stream.tweet_stream()
else:
	print "use proper input, use 1 for help"
	exit()