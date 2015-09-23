import globals
import tweetpony

def previous_tweet():
	try :
		print "%s: %s" % (globals.api.user.screen_name, globals.api.user.status.text)
	except KeyboardInterrupt:
		pass

def tweet_stream():
	try :
		print "%s: %s" % (globals.api.user.screen_name, "Under Construction")
	except KeyboardInterrupt:
		pass