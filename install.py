import requests
import json
import os
import subprocess
import sys

top_dir = os.getcwd() # the directory, where script was invoked

##############################################################
## Functions of this section are "low-level", because
## they are used in process of SDL libraries installation


def get_sdl_source_dir(pref):
    l = os.listdir(top_dir)
    dir = None
    for el in l:
        if pref in el and os.path.isdir(top_dir+"/"+el):
            dir = el

    return os.getcwd()+"/"+dir
def print_delim(s):
    print("-"*20)
    print(s)
    print("-"*20)
    
def unzip(file):
    print("unzipping {}".format(file))

    code = subprocess.call("unzip {}".format(file).split())
    if code != 0:
        print("unable to unzip {}!".format(file))
        exit(-1)
        
    print("sucessfully unzipped {}!".format(file))
def write_release_to_zip(response, zipname, url):
    #write down zip file received from request
    if response.status_code == 200:
        with open(zipname,"wb") as f:
            f.write(response.content)
    else:
        print("failed to download {}".format(url))
        exit(-1)
    print("sucessfully downloaded {}".format(url))
def run_cmake(dir_pref):
    print("start running cmake...")
    
    source_dir = get_sdl_source_dir(dir_pref)
    
    os.chdir(source_dir)
    os.mkdir(source_dir+"/build")

    a = "cmake .. -DCMAKE_INSTALL_PREFIX={}".format(source_dir+"/build")
    os.chdir(source_dir+"/build")
    subprocess.call(a.split())
    subprocess.call("cmake --build .")
    subprocess.call("cmake --build . --target install")
    
    print("finished running cmake!")
def get_releases_list(url, target):
    #get list of all releases
    print("sending request to get latest {} release sources list...".format(target))
    response = requests.get(url)
    if response.status_code == 404:
        print("unable to fetch {} release sources list!".format(target)) 
        exit(-1)
    print("sucessfully got latest {} release sources list!".format(target))
    return response
def get_source_code_url(response):
    # get the latest source code release
    target_json = json.loads(response.content)
    return target_json[0]["assets"][5]["browser_download_url"]
def get_source_code_url_list(response):
    #get list of all available assets
    target_json = json.loads(response.content)
    return [target_json[0]["assets"][n]["browser_download_url"] for n in range(0,10)]

def download_source_code(url):
    print("trying to download {}".format(url))
    return requests.get(url)
#####################################################################    



#######
#Functions to install libraries
######
def get_sdl():
    print_delim("start SDL2 installation...")
    
    release_list_response = get_releases_list("https://api.github.com/repos/libsdl-org/SDL/releases","SDL2")
    source_code = get_source_code_url(release_list_response)
    response  = download_source_code(source_code)
    write_release_to_zip(response,"SDL_source.zip",source_code)
    unzip("SDL_source.zip")
    run_cmake("SDL")
    
    print_delim("finished SDL2 installation!")

def get_sdl_img():
    print_delim("start SDL_image installation...")

    release_list_response = get_releases_list("https://api.github.com/repos/libsdl-org/SDL_image/releases","SDL_image")
    releases = get_source_code_url_list(release_list_response)
    for id, r in enumerate(releases):
        print("{} - {}".format(id,r))
    url_to_download = input("enter url number to download:")
    try:
        url = releases[int(url_to_download)]
    except Exception as e:
        print(str(e))
        exit(-1)

    file = download_source_code(url)
    write_release_to_zip(file,"SDL_image.zip",url)
    try:
        os.mkdir(top_dir+"/SDL2_image")
        os.chdir(top_dir+"/SDL2_image")
        unzip("../SDL_image.zip")
    except Exception as e:
        print(str(e))
        exit(-1)

    print_delim("finished SDL2 installation!")

def get_sdl_ttf():
    print_delim("start SDL_ttf installation...")

    release_list_response = get_releases_list("https://api.github.com/repos/libsdl-org/SDL_ttf/releases","SDL_ttf")
    releases = get_source_code_url_list(release_list_response)
    for id, r in enumerate(releases):
        print("{} - {}".format(id,r))
    url_to_download = input("enter url number to download:")
    try:
        url = releases[int(url_to_download)]
    except Exception as e:
        print(str(e))
        exit(-1)

    file = download_source_code(url)
    write_release_to_zip(file,"SDL_ttf.zip",url)

    try:
        os.mkdir(top_dir+"/SDL2_ttf")
        os.chdir(top_dir+"/SDL2_ttf")
        unzip("../SDL_ttf.zip")
    except Exception as e:
        print(str(e))
        exit(-1)

    print_delim("finished SDL_ttf installation!")
    
##############################


for arg in sys.argv[1:]:
    if arg == "SDL":
        get_sdl()
        os.chdir(top_dir)
    elif arg == "ttf":
        get_sdl_ttf()
        os.chdir(top_dir)
    elif arg == "img":
        get_sdl_img()
        os.chdir(top_dir)
    else:
        print("usage example: install.py [SDL] [ttf] [img]")
        print("you should pass at least one argument to download")
        exit(0)
