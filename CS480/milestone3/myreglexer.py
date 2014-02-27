#!/usr/bin/env python
import collections
import sys
import re

Tokens = None


def enum(**enums):
    return type('Enum', (), enums)
       
def tokenize(stream):
    Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])
       
    tokenSpec = [
        ('REAL',        r'[-]?(?=\d*[.eE])(?=\.?\d)\d*\.?\d*(?:[eE][+-]?\d+)?'),
        ('INTEGER',     r'[-]?[0-9]+'),
        ('STRING',      r'\"(\\.|[^"])*\"'),
        ('BINOP',       r'[\+\-\^\*/%]|([<>]=?|=)|or|and'),
        ('ASSIGN',      r':='),
        ('STATEMENT',   r'stdout|while|if|let'),
        ('UNOP',        r'not|sin|cos|tan'),
        ('TYPES',       r'bool|int|float|string'),
        ('BOOL',        r'true|false'),
        ('NAME',        r'[-]?[a-zA-Z_][a-zA-Z0-9_]+'),
        ('LBRACE',      r'\['),
        ('RBRACE',      r'\]'),
        ('NEWLINE',     r'\n'),
        ('SKIP',        r'[ \t]'),
    ]
 
    tokenRegex = '|'.join('(?P<%s>%s)' % pair for pair in tokenSpec)
       
    nextToken = re.compile(tokenRegex).match
       
    # Setup the line start and current position ...
    pos = lineStart = 0
       
    # ... as well as the current line.
    x = 1
       
    # Fetch the first token ...
    token = nextToken(stream)
       
    # ... and start the processing.
    while token is not None:
        # Fetch the token type ...
        typ = token.lastgroup
          
        # ... and increment line counter if it is a newline.
        if typ == 'NEWLINE':
            lineStart = pos
            x += 1
        elif typ != 'SKIP':
            # Fetch the token value ...
            value = token.group(typ)                
            yield Token(typ, value, x, token.start() - lineStart)
             
        pos = token.end()
        token = nextToken(stream, pos)
    if pos != len(stream):
        print 'Unexpected character %r on line %d' % (stream[pos], x)
        sys.exit(1)
          
def main(argv):
    global Tokens
    lexemes = []
    x = 1

    with open(argv, 'r') as f:
        #data = f.readlines();
        contents = f.read()
    
    for token in tokenize(contents):
        print token
    
if __name__ == "__main__":
   main(sys.argv[1])
