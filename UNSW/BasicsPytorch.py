import torch
import numpy as np
x=torch.empty(3,2,2) ##Creates empty tensor of given size 
print(x)
x=torch.rand(3,2,2);
x=torch.zeros(3,2,2);
x=torch.ones(3,2,2,dtype=torch.float());
y=torch.tensor([1,2]);
#Normal mathematical operatios allowed 
#inplace addition==>
y.add_(x);
#or
z=torch.add(x,y);
z=x+y;
#how to access rows and columns ==> use :
print(x[1,:])#prints first index entire row==> colon stand for whole range
#reshaping
x=torch.rand(4,3);
#using view
y=x.view(12);
y=x.view(-1,6); #pytorch finds value for -1 itself

#converting numpy arrays to tensors

a=torch.ones(5)
b=a.numpy()

c=np.ones(5)
d=torch.from_numpy(c);

#a and b share the same memory. If one is modified other also gets modified automatically similarly for c and d
x=torch.rand(5, requires_grad=True);  ## Flagging a variable later for optimization


