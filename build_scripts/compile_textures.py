import sys
import os

def collect_filenames(from_dir):
    return [ x for x in os.listdir(from_dir) if ".png" in x ] 

def file_name_to_c_name(file_name):
    return "precomped_texture_" + file_name.split(".")[0]

def write_data(path, data: dict):    
    with open(path, "w") as file:
        file.write("#ifndef PRECOMPED_TEXTURES_H \n")
        file.write("#define PRECOMPED_TEXTURES_H \n")

        for name, value in data.items():
            file.write("char " + file_name_to_c_name(name) + "[] = { ")
            for char in value:
                file.write(str(char) + ", ")
            file.write("}; \n")

        file.write("#endif \n")


def compile_textures(from_dir, to_dir):
    file_names = collect_filenames(from_dir)
    print(file_names)

    data = { }

    for file_name in file_names:
        file_path = from_dir + file_name
        with open(file_path, "rb") as file:
            data[file_name] = file.read()

    write_data(to_dir, data);


compile_textures(sys.argv[1], sys.argv[2])
