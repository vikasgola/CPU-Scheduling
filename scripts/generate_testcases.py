import random

def generate(filename):
    with open(filename, "w+") as f:
        n = random.randint(2,10)
        f.write(str(n)+"\n")
        jobtype = ["C", "C", "C", "C", "I", "O"]
        for i in range(n):
            line = str(100+i)+ " " + str(random.randint(2, 12)) + " "
            line += str(random.randint(1, 100))+ " " + str(random.randint(1, 100)) + " "
            j = random.randint(1, 10)
            for _ in range(j):
                line += str(jobtype[random.randint(0,5)])+ " " + str(random.randint(1, 10)) + " "
            line += "-1"
            f.write(line+"\n")

if __name__ == "__main__":
    for i in range(10):
        generate("test_cases/test_case_{}.dat".format(i))