#include<bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
const ld eps = 1e-10;

struct Point{
    ll x,y,num;
    Point(ll x=0, ll y=0, ll num=0):x(x),y(y),num(num){}
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

ll operator * (Vector a,Vector b){return a.x*b.x+a.y*b.y;} // 点乘
ll cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;} // 叉乘
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
ll area2(Point *p, int n){ // 凸多边形面积
    ll res = 0;
    for(int i=1;i<=n;i++) res += cross(p[i],p[i%n + 1]);
    return abs(res); // 避免转错方向
}

struct Line{
    Point u,v;
    Line(Point u=Point(), Point v=Point()):u(u),v(v){} // 两点式
    Line(Point u=Point(), ld k=0):u(u),v(u+Point(1,k)){} // 点斜式
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


void convex(Point *pos, Point *res, int n, int &num){ // 求凸包
    num = 0;
    sort(pos+1,pos+n+1);
    for(int i=1;i<=n;i++){
        while(num>1 && cross(res[num]-res[num-1],pos[i]-res[num-1])<=0){
            num--;
        }
        res[++num] = pos[i];
    }
    int k = num;
    for(int i=n-1;i>=1;i--){
        while(num>k && cross(res[num]-res[num-1],pos[i]-res[num-1])<=0){
            num--;
        }
        res[++num] = pos[i];
    }
    if(n>1) num--;
}

const int N = 1e5+10;
int T,n,n2,num1,num2;
Point pos[N],inpos[N],cov1[N],cov2[N];
bool vis[N];
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        n2 = 0;
        ll x,y;
        for(int i=1;i<=n;i++){
            vis[i] = 0;
            scanf("%lld %lld",&x, &y);
            pos[i] = Point(x,y,i);
        }

        convex(pos,cov1,n,num1);
        if(num1 == n){
            cout<<"-1"<<endl;
            continue;
        }
        for(int i=1;i<=num1;i++){
            vis[cov1[i].num] = 1;
        }
        for(int i=1;i<=n;i++){
            if(!vis[pos[i].num]){
                inpos[++n2] = pos[i];
            }
        }
        convex(inpos,cov2,n2,num2);
        // for(int i=1;i<=num2+1;i++){
        //     cout<<cov2[i].x<<cov2[i].y<<endl;
        // }

        ll minar = 7e18,ta,pin,tot,now;
        tot = area2(cov1,num1);
        Point tri[5];
        tri[1] = cov1[1], tri[2] = cov1[2];
        for(int i=1;i<=num2;i++){
            tri[3] = cov2[i];
            ta = area2(tri,3);
            if(ta<minar){
                minar = ta;
                pin = i;
            }
        }

        tri[3] = cov2[pin];
        for(int i=1;i<=num1;i++){
            tri[1] = cov1[i],tri[2] = cov1[i+1];
            ta = area2(tri,3);
            while(1){
                tri[3] = cov2[pin%num2 + 1];
                now = area2(tri,3);
                if(now>ta){
                    tri[3] = cov2[pin];
                    break;
                }
                else if(now == ta){
                    pin = pin%num2 + 1;
                    tri[3] = cov2[pin];
                    break;
                }
                pin = pin%num2 + 1;
                ta = now;
            }
            minar = min(minar,ta);
        }
        //cout<<tot<<endl;
        printf("%lld\n",tot-minar);
    }
    return 0;
}