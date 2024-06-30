import torch

x=torch.rand(3, requires_grad=True);
y=x+2
print(y)
z=y*y*2 ##specifies the grad function along with
print(z)
z=z.mean()  #returns single value mean of z
# grad for single value z wouldnt work for tensor of z with higher size
z.backward() #dz/dx #call backward to calc gradient
print(x.grad)
# for higher size tensor instead of single value pass a tensor of same size as z as input to the backward function
v=torch.tensor([1.0,1.0,1.0], dtype=torch.float32)
z.backward(v)
print(x.grad)
#M1 to avoid gradient tracking

x.requires_grad_(False)

#M2 
y=x.detach()

#M3
with torch.no_grad():
    y=x+2
    #y has no gradient function

weights=torch.ones(4, requires_grad=True)

for epochs in range(1):
    model_output= (weights*3).sum()

    model_output.backward()  #Creates the gradients of model_output

    print(weights.grad)

    #after every iteration make grads zero
    weights.grad.zero_()

optimizer = torch.optim.SGD(weights, lr=0.01)
optimizer.step()
optimizer.zero_grad()##Do at every step
