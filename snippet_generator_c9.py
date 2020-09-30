input_file = [*open("./test.in", "r")]
output_file = open("/home/ubuntu/.c9/snippets/c_cpp.snippets", "a")

name = input_file[0]
output_file.write("\n# ==============================================")
output_file.write(f"\nsnippet {name}")
for i in input_file[1:]:
    output_file.write("\t"+i.replace("    ", "\t"))
output_file.write("\n# ==============================================\n")