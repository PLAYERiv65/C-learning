import ssl
import whois
import builtwith

ssl._create_default_https_context = ssl._create_unverified_context
print(builtwith.parse('http://www.bootcss.com/'))