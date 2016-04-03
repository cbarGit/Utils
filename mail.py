#! /usr/bin/python

import sys
import smtplib
import netrc

#create a file in your home directory called
#".netrc" and put in it something like
#machine test
#        login your_username
#        password your_password

from_addr = 'Sender'
to_addrs  = 'your@mail.com'
subj = 'Subject'
message_text = 'Hi ' + sys.argv[1]  +  ' !'
msg = "From: %s\nTo: %s\nSubject: %s\n\n%s" % ( from_addr, to_addrs, subj, message_text )

# Read from the .netrc file in your home directory
HOST = 'test'
secrets = netrc.netrc()
username, account, password = secrets.authenticators( HOST )


# The actual mail send
server = smtplib.SMTP('smtp.gmail.com:587')
server.starttls()
server.login(username,password)
server.sendmail(from_addr, to_addrs, msg)
server.quit()
