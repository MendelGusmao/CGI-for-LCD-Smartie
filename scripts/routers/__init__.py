import sys, __main__

def main():
    if (len(sys.argv) > 1):
        params = sys.argv[1].split("#")
        function = params[0]
    
        if (function):
            func = getattr(__main__, function, None)
            if (callable(func)):
                args = {} if len(params) == 1 else params[1].split(";")
                print(func(*args))
            else:
                print("[CGI4LCD] Function '%s' not found\n" % function)
        
        sys.exit()