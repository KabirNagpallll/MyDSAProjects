
# ##################################MANUALLY####################################################################
# import numpy as np

# #f=w*x
# #f=2*x
# X=np.array([1,2,3,4], dtype=np.float32)
# Y=np.array([2,4,6,8], dtype=np.float32)

# #initialsizing w
# w=0.0

# #model prediction==> First make forward pass funnction 
# def forward(x):
#     return w*x
# #loss= Mean squared error (MSE)
# def loss(y, y_pred):
#     return ((y-y_pred)**2).mean()

# #gradient
# #MSE= 1/N*(w*x-y)**2
# #dJ/dw=1/N*(2x)(w*x-y)
# def gradient(x,y, y_pred):
#     return np.dot(2*x,(y_pred-y)).mean() ##order matters (if ulta==> explode)

# print(f'Prediction before training: f(5)= {forward(5):.3f}')

# #Training 
# learning_rate=0.01
# n_iters= 10

# for epochs in range(n_iters):
#     y_pred=forward(X)
#     #loss
#     l = loss(Y,y_pred)

#     #grad==> dJ/dw
#     dw=gradient(X,Y,y_pred)

#     #update weights
#     w-=learning_rate*(dw)

#     if epochs%1==0:
#         print(f'epochs {epochs + 1}: w= {w:.3f}, loss={l:.8f}')

# print(f'Prediction after training: f(5)= {forward(5):.3f}')

#############################Using Autograd##################################
##This approach works with high epochs as compared to completely manual
import torch
X=torch.tensor([1,2,3,4], dtype=torch.float32)
Y=torch.tensor([2,4,6,8], dtype=torch.float32)

#initialsizing w
w=torch.tensor(0.0, dtype=torch.float32, requires_grad=True)

#model prediction==> First make forward pass funnction 
def forward(x):
    return w*x
#loss= Mean squared error (MSE)
def loss(y, y_pred):
    return ((y-y_pred)**2).mean()

#No separate function for grad

print(f'Prediction before training: f(5)= {forward(5):.3f}')

#Training 
learning_rate=0.01
n_iters= 1000

for epochs in range(n_iters):
    y_pred=forward(X)
    #loss
    l = loss(Y,y_pred)

    #grad==> dJ/dw
    l.backward()
    dw=w.grad

    #update weights
    #To avoid multiple gradient addition (To avoid the continuos addition over steps)==> dont let it be the part of the computational graph
    with torch.no_grad():
        w-=learning_rate*(dw)
    ##To avoid addition w again and again
    w.grad.zero_()
    if epochs%10==0:
        print(f'epochs {epochs + 1}: w= {w:.3f}, loss={l:.8f}')

print(f'Prediction after training: f(5)= {forward(5):.3f}')


###################################