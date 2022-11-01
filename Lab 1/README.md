# Лабораторная работа по курсу "Искусственный интеллект"
# Многослойный персептрон

| Студент | *калугин Кирилл Алексеевич* |
|------|------|
| Группа  | *7* |
| Оценка 1 (свой фреймворк) | *X* |
| Оценка 2 (PyTorch/Tensorflow) | *X* |
| Проверил | Сошников Д.В. |

> *Комментарии проверяющего*
### Задание

Решить задачу классификации для датасетов MNIST, FashionMNIST, CIFAR-10 с помощью 1, 2 и 3-слойного персептрона. Попробовать разные передаточные функции, провести сравнительную оценку решений. Решение сделать двумя способами:
* "С нуля", на основе базовых операций библиотеки numpy. Решение желательно реализовать в виде библиотеки, пригодной для решения более широкго круга задач.
* На основе одного из существующих нейросетевых фреймворков, в соответствии с вариантом задания:
   1. PyTorch
   1. Tensorflow/Keras

> *Номер варианта вычисляется по формуле 1 + (N-1) mod 2, где N - номер студента в списке.*

Решение оформить в файлах [Solution_MyFramework.ipynb](Solution_MyFramework.ipynb) и [Solution.ipynb](Solution.ipynb). 
Отчет по работе и сравнение методов пишется в этом файле после задания.
### Критерии оценки

Первая часть лабораторной работы:

| Сделано | Баллы |
|---------|-------|
| Реализован однослойный персептрон, классифицирующий датасет с точностью >85% | 1 |
| Реализован многослойный персептрон, классифицирующий датасет с точностью >85% | 2 |
| Реализация сделана как библиотека для обучения сетей различных конфигураций, в соответствии с примером | 1 |
| Улучшена архитектура библиотеки, отдельно вынесены алгоритмы обучения, функции потерь | 3 |
| Проведено сравнение различных гиперпараметров, таких, как передаточные функции, число нейронов в промежуточных слоях, функции потерь, с графиками обучения и матрицами неточности | 2 |
| Проведен анализ для датасета FashionMNIST | 1 |

Вторая часть лабораторной работы:

| Сделано | Баллы |
|---------|-------|
| Реализован однослойный персептрон, классифицирующий датасет с точностью >85% | 1 |
| Реализован многослойный персептрон, классифицирующий датасет с точностью >85% | 2 |
| Реализация использует возможности базового фреймворка, включая работу с данными | 3 |
| Проведено сравнение различных гиперпараметров, таких, как передаточные функции, число нейронов в промежуточных слоях, функции потерь, с графиками обучения и матрицами неточности | 2 |
| Проведен анализ для датасета FashionMNIST | 1 |
| Проведен анализ для другого датасета с цветными картинками (CIFAR-10) | 1 |

## Отчёт по работе

Отчёт, помимо общего описания решения, должен включать:
* График точности на обучающей и проверочной выборке в процессе обучения
* Confusion Matrix
* Сравнение полученных показателей точности модели для различных гиперпараметров (передаточных функций, числа нейронов в слоях и т.д.)

### Первая часть

В данной части лабораторной работы реализована библиотека Net.

Также реализованы :

Функция потерь Crossentropy Loss
Функция потерь Mean Square Error
Линейный слой Linear
Предаточная функция Tanh
Предаточная функция ReLU
Функция Softmax
Метод наискорейшего градиентного спуска

#### Лучшие результаты:

##### MNIST

- 90% для однослойной сети
![image](https://user-images.githubusercontent.com/71846372/198027714-56827868-be06-400a-888d-087cf2439b3a.png)

- 87% для многослойной сети
![image](https://user-images.githubusercontent.com/71846372/198027823-9a2f027d-1711-4172-9516-6295596fb333.png)

##### FashionMNIST

- 10% для однослойной сети
![image](https://user-images.githubusercontent.com/71846372/198028447-6723a280-a470-4c44-8c9c-f4b59dac29d3.png)

- 83% для многослойной сети
![image](https://user-images.githubusercontent.com/71846372/198028480-09623fff-fd4c-4331-8683-d8966ca481b0.png)

#### Выводы

В данной части работы я лучше узнал и разобрался в том, что находится "под капотом" у нейронных сетей. К сожалению, точность оставляет желать лучшего, тк она достигается очень точным подбором гиперпараметров. В целом, повышения точности можно добится уменьшением размера батча и увеличением количества эпох, однако это сильно замедляет обучение модели. Также, я заметил, что оптимизатор Adam работает лучше других, однако требует уменьшения learning rate'а, иначе "проскакивает" мимо нужных значений. Количество нейронов в скрытых слоях также влияет на точность, но не так существенно.

### Вторая часть

В данной части работы я работал с датасетами MNIST, FashionMNIST и CIFAR-10, используя библиотеки Tensorflow и Keras.

#### Лучшие результаты:

##### MNIST

- 92% для однослойной сети
![image](https://user-images.githubusercontent.com/71846372/198030692-bdebe6d3-c628-44ec-9c22-5beaccd0b903.png)

- 99% для многослойной сети
![image](https://user-images.githubusercontent.com/71846372/198030805-de023f0f-751b-4fae-8bd8-1a846bbcc586.png)

##### FashionMNIST

- 85% для однослойной сети
![image](https://user-images.githubusercontent.com/71846372/198030877-6c100ec1-972c-4a7a-8c99-fa17ffc4967e.png)

- 91% для многослойной сети
![image](https://user-images.githubusercontent.com/71846372/198030923-510d1d92-f569-4f78-94ed-655cdb5011c7.png)

##### CIFAR-10

- 40% для однослойной сети
![image](https://user-images.githubusercontent.com/71846372/198031015-de7bbcd4-b12f-4dc3-b69c-34a1292e759e.png)

- 64% для многослойной сети
![image](https://user-images.githubusercontent.com/71846372/198031200-5a525b90-fae3-4aba-af68-66e091582b25.png)

#### Выводы

В данной части работы я научился пользоваться библиотеками Tensorflow и Keras. Они существенно упрощают создание и использование нейронных сетей. Кроме того, данные библиотека обладает достаточно широким функционалом, который позволяет быстро отслеживать изменение параметров сети. Было очень интересно наблюдать за изменением точности предсказаний с изменением гиперпараметров. В итоге, я даже смог добится почти стопроцентной точности на датасете MNIST. Теперь я намного лучше понимаю, как работают разнообразные системы распознавания рукописного ввода. Однако, даже при этом, модель все еще требует совершенствоания, тк на более сложных датасетах, вроде CIFAR-10, ее точность сильно падает.

## Codespaces

По возможности, используйте GitHub Codespaces для выполнения работы. По результатам, дайте обратную связь:
1. Что понравилось?
1. Что не понравилось?
1. Какие ошибки или существенные затруднения в работе вы встречали? (По возможности, будьте как можно более подробны, указывайте шаги для воспроизведения ошибок)

## Материалы для изучения

 * [Реализация своего нейросетевого фреймворка](https://github.com/shwars/NeuroWorkshop/blob/master/Notebooks/IntroMyFw.ipynb)
 * [Введение в PyTorch](https://github.com/shwars/NeuroWorkshop/blob/master/Notebooks/IntroPyTorch.ipynb)
 * [Введение в Tensorflow/Keras](https://github.com/shwars/NeuroWorkshop/blob/master/Notebooks/IntroKerasTF.ipynb)