
import sys, getopt, os


def InsertResImpl(file, name, tag, path):
    file.write('%s %s "%s"\n' % (name, tag, path.replace('\\','\\\\') ))

def InsertRes(file, dir, dir_name, tag):
    dir_path = os.path.join(dir, dir_name)
    for file_name in os.listdir(dir_path):
        file_path = dir_path+"\\"+file_name
        if os.path.isfile(file_path):
            InsertResImpl(file,file_name.upper(),tag, dir_name+"\\"+file_name)

def main(argv):
    resdir = ''
    try:
        opts, args = getopt.getopt(argv,"hd:",["resdir="])
    except getopt.GetoptError:
        print ('ScanRes.py -d')
        sys.exit(2)
        
    for opt, arg in opts:
        if opt == '-h':
            print ('ScanRes.py -d <resdir>')
            sys.exit()
        elif opt in ("-d","--resdir"):
            resdir = arg
    
    template_file = open(resdir + "/RCTemplate",'r')
    dst_file=open(resdir+"/Resource.rc",'w')
    
    dst_file.write(template_file.read())

    InsertRes(dst_file, resdir, "res\\lua\\LuaCore","LUACORE")
    InsertRes(dst_file, resdir, "res\\lua\\LuaChar","LUACHAR")
    InsertRes(dst_file, resdir, "res\\img","IMAGES")

    template_file.close()
    dst_file.close()


if __name__ == "__main__":
   main(sys.argv[1:])