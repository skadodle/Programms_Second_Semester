import secrets
import argparse
import string


def read_pasws_from_file():
    mas = []
    with open("not_correct_passwords.txt", "r") as file:
        mas = [i for i in file]
    return mas


def is_valid_password(password):
    if not(any(i in string.ascii_letters for i in password)):
        return False
    if not(any(i in string.punctuation for i in password)):
        return False
    if not(any(i in string.digits for i in password)):
        return False
    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-l', '--length')
    parser.add_argument('-c', '--count')
    parser.add_argument('-w', '--write')
    args = parser.parse_args()
    length = int(args.length) if args.length else 16
    count = int(args.count) if args.count else 1
    file_to_write = args.write if args.write else "None"

    not_correct_passwords = read_pasws_from_file()

    alphabet = string.ascii_letters + string.digits + string.punctuation

    if file_to_write != "None":
        with open(file_to_write, "w") as file:
            for i in range(count):
                while True:
                    password = ''.join(secrets.choice(alphabet)
                                       for i in range(length))
                    if is_valid_password(password) == False:
                        password = ""
                        continue
                    if password not in not_correct_passwords:
                        file.write(password)
                        file.write("\n")
                        break
    else:
        for i in range(count):
            while True:
                password = ''.join(secrets.choice(alphabet)
                                   for i in range(length))
                if is_valid_password(password) == False:
                    password = ""
                    continue
                if password not in not_correct_passwords:
                    print(password)
                    break
