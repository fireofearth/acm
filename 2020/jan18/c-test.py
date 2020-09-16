import subprocess

def lists_to_str(*ls):
    o = ''
    for l in ls:
        for i in l:
            o += str(i) + ' '
    return o

def execute(args, to_stdin=None):
    '''
    based on https://stackoverflow.com/a/4417735
    '''
    popen = subprocess.Popen(args,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True)
    out, err = popen.communicate(input=to_stdin)
    return out, err, popen.returncode


def test(o, e, expected=None):
    if e:
        print(e)
        return
    o = o.splitlines()[0]
    print(o)

def run(args, to_stdin=None, expected=None):
    if type(to_stdin) is list:
        to_stdin = lists_to_str(to_stdin)
    o, e, _ = execute(args, to_stdin)
    test(o, e, expected)

args = ['k']



items = '''
4
2 1 4 3
'''
expected = '1 2 1 2'
run(args, to_stdin=items, expected=expected)
#
items = [6, 2,1,4,3,6,5]
expected = [1,2,1,2,1,2]
run(args, to_stdin=items, expected=expected)
#
items = [6, 2,1,4,5,6,3]
expected = [1,2,1,2,1,2]
run(args, to_stdin=items, expected=expected)
#
items = '''
11
2 3 1  5 4  7 8 9 10 11 6
'''
expected = [1,2,3, 4,5, 1,2,3,1,2,3]
run(args, to_stdin=items, expected=expected)
#
items = '''
11
4 3 2 1 6 5 7 10 11 9 8
''' # (1 4) (2 3) (5 6) (7) (8 10 9 11)
expected = ['1 1 4 4 1 4 7 1 1 4 4']
run(args, to_stdin=items, expected=expected)




