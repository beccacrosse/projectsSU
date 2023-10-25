export default class Point {  // default gets imported without curly braces in file index
  // usually import default best with only one class, otherwise u can have no default classes but doesnt rly matter
  constructor(x, y){
    this.x = x;
    this.y = y;
    this.privateVar = 42; //if something shouldnt be accessed mark it as private
  }

  move(dx, dy){
    this.x = dx;
    this.y = dy;
  }

  toString(){
    return (($this.x), $(this.y));
  }
}

window.Point = Point;

export class Rect{
  constructor(topLeft, width, height){
    this.topLeft = topLeft;
    this.width = topLeft;
    this.height = height;
  }
}

window.Rect = Rect;