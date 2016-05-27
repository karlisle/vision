
import theano

from theano import tensor as T
from theano.tensor.nnet import  conv2d
from theano.tensor.signal import  downsample
import numpy
import pylab
from PIL import Image


def convOp():

    rng = numpy.random.RandomState(23455)

    # Instanciar un tensor 4D como entrada
    input = T.tensor4(name='input')

    # Inicializar las variables compartidas par los pesos

    w_shp = (2,3,9,9)
    w_bound = numpy.sqrt(3*9*9)
    W = theano.shared(numpy.asarray(rng.uniform(low= -1.0 / w_bound, high= 1.0 /w_bound, size= w_shp), dtype=input.dtype), name='W')

    b_shp = (2, )
    b = theano.shared(numpy.asarray(rng.uniform(low=-.5, high=.5, size=b_shp), dtype=input.dtype), name='b')

    # Construir la expresion simbolica que calcule la convolucion de la entrada en w

    conv_out = conv2d(input, W)

    output = T.nnet.sigmoid(conv_out + b.dimshuffle('x', 0, 'x', 'x'))

    # Crear una funcionde theano para computar las imagenes filtradas
    f = theano.function([input], output)

    img = Image.open('/home/kharl/Documents/vision/cnn/wolfmoon.jpg')

    img = numpy.asarray(img, dtype='float64') / 256

    image = img.transpose(2, 0, 1).reshape(1, 3, 639, 516)
    filtered_img = f(image)

    pylab.subplot(1, 3, 1); pylab.axis('off'); pylab.imshow(img)
    pylab.gray();

    pylab.subplot(1,3,2); pylab.axis('off'); pylab.imshow(filtered_img[0, 0, :, :])
    pylab.subplot(1,3,3); pylab.axis('off'); pylab.imshow(filtered_img[0, 1, :, :])

    pylab.show();

    print('Ok, fine!!')
    pass

def maxPooling():
    input = T.dtensor4('input')
    maxpool_shape = (2, 2)
    pool_out = downsample.max_pool_2d(input, maxpool_shape, ignore_border=True)
    f = theano.function([input], pool_out)

    invals = numpy.random.RandomState(1).rand(3, 2, 5, 5)
    print('With ignore_border set true: ')
    print('invals[0, 0, :, :] = \n', invals[0, 0, :, :])
    print('output[0, 0, :, :] = \n', f(invals)[0, 0, :, :])

    pool_out = downsample.max_pool_2d(input, maxpool_shape, ignore_border=False)
    f = theano.function([input], pool_out)
    print('With ignore_border set False: ')
    print('invals[1, 0, :, :] = \n', invals[1, 0, :, :])
    print('output[1, 0, :, :] = \n', f(invals)[1, 0, :, :])
    pass

maxPooling()