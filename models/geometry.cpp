#include<bits/stdc++.h>
using namespace std;
#define ld long double
const ld eps = 1e-10;

struct Point{
    ld x,y;
    Point(ld x=0, ld y=0):x(x),y(y){}
};
typedef Point Vector;

bool eq(ld a, ld b){return fabs(a-b)<eps;} // 判断浮点数是否相等
ld sign(ld a){if(eq(a,0)) return 0; return a>0?1:-1;} // 符号
bool operator == (Point a, Point b){return eq(a.x,b.x) && eq(a.y,b.y);} // 判断点是否相等
bool operator < (Point a, Point b){return eq(a.x,b.x)?a.y<b.y:a.x<b.x;} // 点排序

Vector operator + (Vector a, Vector b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a, Vector b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (Vector a, ld k){return Vector(a.x*k,a.y*k);}
Vector operator / (Vector a, ld k){return Vector(a.x/k,a.y/k);}

ld operator * (Vector a,Vector b){return a.x*b.x+a.y*b.y;} // 点乘
ld cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;} // 叉乘
ld length(Vector a){return sqrt(a*a);} // 求向量长度
ld distance(Point a, Point b){return length(a-b);} // 求两点距离

ld angle(Vector a, Vector b){ // 求向量a和b的夹角
    return acos((a*b)/length(a)/length(b));
}
Vector rotate(Vector a, ld rad){ // 逆时针旋转rad弧度
    return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}
Vector normal(Vector a){ // 求向量a的单位法向量
    ld l = length(a);
    return Vector(-a.y/l,a.x/l);
}
ld area(Point *p, int n){ // 凸多边形面积
    ld res = 0;
    for(int i=0;i<n;i++) res += cross(p[i],p[(i+1)%n]);
    return abs(res)/2; // 避免转错方向
}


struct Line{
    Point u,v;
    Line(Point u=Point(), Point v=Point()):u(u),v(v){} // 两点式
    Line(Point u=Point(), ld k=0):u(u),v(u+Point(1,k)){} // 点斜式
    Line(ld k=0, ld b=0){
        u = Point(0,b);
        v = Point(1,k+b);
    } // 斜截式
};
Point cross_point(Line a, Line b){ // 求两直线交点
    ld s1 = cross(a.v-a.u,b.u-a.u);
    ld s2 = cross(a.v-a.u,b.v-a.u);
    return (b.u*s2-b.v*s1)/(s2-s1);
} // 类似定比分点公式
ld distance(Point p, Line l){ // 点到直线距离
    return fabs(cross(l.v-l.u,p-l.u)/length(l.v-l.u));
}
ld distance(Point p, Point A, Point B){ // 点到线段AB
    if(A==B) return distance(p,A);
    Vector v1 = B-A, v2 = p-A, v3 = p-B;
    if(sign(v1*v2)<0) return length(v2);
    if(sign(v1*v3)>0) return length(v3);
    return fabs(cross(v1,v2)/length(v1));
}

struct Circle{
    Point o;
    ld r;
    Circle(Point o=Point(), ld r=0):o(o),r(r){}
};
ld distance(Line l, Circle c){ // 直线到圆距离
    return fabs(distance(c.o,l)-c.r);
}


void convex(Point *pos, Point *res, int n, int &num){ // 求凸包
    num = 0;
    sort(pos+1,pos+n+1);
    for(int i=1;i<=n;i++){ // 下凸壳，逆时针转
        while(num>1 && cross(res[num]-res[num-1],pos[i]-res[num-1])<=0) num--;
        res[++num] = pos[i];
    }
    int k = num;
    for(int i=n-1;i>=1;i--){ // 上凸壳，逆时针转
        while(num>k && cross(res[num]-res[num-1],pos[i]-res[num-1])<=0) num--;
        res[++num] = pos[i];
    }
    if(n>1) num--;
}

const int N = 1e5+10;
int n,num;
Point pos[N],res[N];
ld ans=0;
int main(){
    cin>>n;
    ld x,y;
    for(int i=1;i<=n;i++){
        scanf("%Lf %Lf",&x,&y);
        pos[i] = Point(x,y);
    }
    convex(pos, res, n, num);
    for(int i=1;i<=num;i++){
        ans += distance(res[i],res[i%num+1]);
    }
    printf("%.2Lf",ans);
    return 0;
}