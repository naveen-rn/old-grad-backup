import globals
import tweetpony

def tweet_hello():
	globals.user = globals.api.user
	#print "Hello, @%s!" %globals.user.screen_name

def tweet_get():
	tweet  = raw_input("tweet@%s:"%globals.user.screen_name)
	count = len(tweet)

	while count >= 140: 
		tweet = raw_input("tweet(>140)@%s:"%globals.user.screen_name) 
		count = len(tweet)
	
	return tweet

def tweet_post(tweet_value):
	try:
		globals.api.update_status(status = tweet_value)
	except tweetpony.APIError as err:
    		print "Oops, something went wrong! Twitter returned error #%i and said: %s" % (err.code, err.description)
	else:
    		print "Hurray! Tweet has been posted!"