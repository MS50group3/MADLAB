rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x];
/*north*/
if(rg -> arr[x, (y+1)]) == OPEN;
{
rcSprite.y = rg -> arr[y+1];
rcSprite.x = rg -> arr[x];
}else{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x];
}
/*south*/
if (rg -> arr[x][(y-1)]) == OPEN)
{
rcSprite.y = rg -> arr[y-1];
rcSprite.x = rg -> arr[x];
}else{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x];
}
/*east*/
if (rg -> arr[x+1][y)]) == OPEN)
{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x+1];
}else{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x];
}
/*west*/
if (rg -> arr[x-1][y)]) == OPEN)
{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x-1];
}else{
rcSprite.y = rg -> arr[y];
rcSprite.x = rg -> arr[x];