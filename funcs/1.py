import string
import re


def del_spaces(str):
    return str.replace(" ", "")


def check_string(str):
    name, city, birthday_date = str.split('-')
    name = del_spaces(name)
    city = del_spaces(city)
    birthday_date = del_spaces(birthday_date)

    def x(symb): return not(ord(symb.lower())
                            < 1072 or ord(symb.lower()) > 1103)
    temp_name = list(map(x, name))

    if not all(temp_name):
        print("ФИО", name, "не на русском языке!")
        return False
    if city not in ["Москва", "Питер", "Липецк"]:
        print("Город", city, "не в списке: Москва, Питер, Липецк.")
        return False
    if not is_valid_date(birthday_date):
        print("Неправильная дата!", birthday_date)
        return False
    print(name, city, birthday_date)
    return True


def is_valid_date(date):
    result = re.match(
        r'([0-2][0-9]|[3][0-1]|[0-9])\.(0?[0-9]|[1][0-2])\.([2][0][0-1][0-9]|[2][0][2][0-3])', date)
    return result != None


if __name__ == "__main__":
    check_string("Кудрявцев Вячеслав Николаевич - Москва - 05.03.2004")
    check_string("Косов Григорий Валерьевич - Питер - 23.09.2011")
    check_string("Petr Visgalov - Питер - 23.09.2011")
    check_string("Шевченко Иван Дмитриевич - Омск - 23.09.2011")
    check_string("Кортос Владимир Витальевич - Питер - 23.19.2011")
    check_string("Кортос Владимир Витальевич - Питер - 31.09.2011")
    check_string("Кортос Владимир Витальевич - Питер - 23.19.2011")
    check_string("Кортос Владимир Витальевич - Питер - 34.9.2022")
