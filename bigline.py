with open("bigline.txt", "w") as f:
    f.write("A" * 100000 + " needle " + "B" * 100000 + "\n")
    f.write("normal line\n")
