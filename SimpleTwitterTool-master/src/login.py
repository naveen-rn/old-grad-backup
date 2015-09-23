import globals
import developer_details
import tweetpony

def verify_login():
	api = tweetpony.API(consumer_key 		= globals.CONSUMER_KEY, 
					consumer_secret 	= globals.CONSUMER_SECRET, 
					access_token 		= globals.ACCESS_TOKEN, 
					access_token_secret = globals.ACCESS_TOKEN_SECRET)
	globals.api  = api
