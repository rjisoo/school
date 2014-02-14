#!/usr/bin/python
import collections
import sys
import re
       
def tokenize(stream):
    Token = collections.namedtuple('Token', ['typ', 'value', 'line', 'column'])
       
    tokenSpec = [
        ('BINOP',       r'(?<![\+\-\^\*/%])[\+\-]|([<>]=?|=)|[\^\*/%]'),
        ('INTEGER',     r'^-?[0-9]+$'),
        ('REAL',        r'[-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?'),
        ('STATEMENT',   r'stdout|while|if|let|:='),
        ('STRING',      r'(?:"(?:[^"\\n\\r\\\\]|(?:"")|(?:\\\\x[0-9a-fA-F]+)|(?:\\\\.))*")|(?:\'(?:[^\'\\n\\r\\\\]|(?:\'\')|(?:\\\\x[0-9a-fA-F]+)|(?:\\\\.))*\')'),
        ('UNOP',        r'not|sin|cos|tan'),
        ('VARIABLEID',  r'[-]?[a-zA-Z_][a-zA-Z0-9_]*(?!([ \t]+)?\()'),
        ('LBRACE',      r'[\[]'),
        ('RBRACE',      r'[\]]'),
        ('NEWLINE',     r'\n'),
        ('SKIP',        r'[ \t]'),
        ('TYPES',       r'bool|int|float|string'),
        ('BOOL',        r'true|false'),
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
        raise RuntimeError('Unexpected character %r on line %d' % (stream[pos], x))
          
'''def main(argv):
    lexemes = []
    x = 1

    with open(argv, 'r') as f:
        #data = f.readlines();
        contents = f.read()
    
    for token in tokenize(contents):
        print token
    
if __name__ == "__main__":
   main(sys.argv[1])'''
