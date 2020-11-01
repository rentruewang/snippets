import re
import sys
from datetime import datetime

import apache_log_parser

# 64.242.88.10 - - [07/Mar/2004:16:11:58 -0800] "GET /twiki/bin/view/TWiki/WikiSyntax HTTP/1.1" 200 7352
parser = apache_log_parser.make_parser('%h - - %t "%r" %s %b')


for line in sys.stdin:
    fields = parser(line)
    key = fields["time_received_datetimeobj"].replace(minute=0, second=0)
    value = fields["time_received_isoformat"]
    print("{}\t{}".format(key, value), file=sys.stdout)
