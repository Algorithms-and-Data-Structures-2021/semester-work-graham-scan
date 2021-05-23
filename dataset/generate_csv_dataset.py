import argparse
from random import randint
from pathlib import Path

DEFAULT_DESCRIPTION = 'CSV dataset generator script'
DEFAULT_DATASETS = 5
DEFAULT_ELEMENTS = 500
DEFAULT_MAX_COORD = 1000
DEFAULT_MIN_COORD = 0


def parse_args():
    """
    Парсинг аргументов командной строки (CLI).
    :return интерфейс для работы с аргументами.

    Больше информации на https://docs.python.org/3.7/howto/argparse.html
    """
    parser = argparse.ArgumentParser(description=DEFAULT_DESCRIPTION)

    parser.add_argument('--datasets',
                        type=int,
                        default=DEFAULT_DATASETS,
                        help='the number of datasets to generate (default: {})'.format(DEFAULT_DATASETS))

    parser.add_argument('--elements',
                        type=int,
                        default=DEFAULT_ELEMENTS,
                        help='number of elements in dataset (default: {})'.format(DEFAULT_ELEMENTS))

    return parser.parse_args()


if __name__ == '__main__':
    args = parse_args()

    # валидация аргументов
    if args.datasets <= 0:
        raise ValueError('Number of samples must be greater than 0.')
    if args.elements <= 0:
        raise ValueError('Number of elements must be greater than 0.')
    
    # Открываем папку для записи результатов
    output = f'data/{args.elements}/'
    Path(output).mkdir(parents=True, exist_ok=True)
    
    # Генерируем нужное кол-во наборов
    for dataset in range(args.datasets):
        with open(output + f'{dataset + 1}.csv', 'w') as file:
            for i in range(args.elements - 1):
                x = randint(DEFAULT_MIN_COORD, DEFAULT_MAX_COORD)
                y = randint(DEFAULT_MIN_COORD, DEFAULT_MAX_COORD)
                file.write('{} {}\n'.format(x, y))
            x = randint(DEFAULT_MIN_COORD, DEFAULT_MAX_COORD)
            y = randint(DEFAULT_MIN_COORD, DEFAULT_MAX_COORD)
            file.write('{} {}'.format(x, y))
