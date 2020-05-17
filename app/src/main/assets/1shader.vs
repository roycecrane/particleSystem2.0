#version 300 es
layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec3 vel_in;
layout(location = 2) in vec3 FBDAT_in;
layout(location = 3) in vec3 initPos_in;

uniform vec3 touch;
uniform vec3 seeker;
uniform vec3 button;
uniform vec3 time;
out vec3 pos_out;
out vec3 vel_out;
out vec3 FBDAT_out;
out vec3 initPos_out;
out vec3 B;
float pi = 3.14159265359f;
void color(float e, out vec3 FBDAT_out){
    if(e <= 0.1f ){FBDAT_out=vec3(1.0,1.0,1.0);}
    if(e <= 0.2f && e > 0.1f) FBDAT_out=vec3(0.5,0.5,0.0);
    if(e <= 0.3f && e > 0.2f) FBDAT_out=vec3(0.0,0.5,0.0);
    if(e <= 0.4f && e > 0.3f) FBDAT_out=vec3(0.5,0.3,0.0);
    if(e <= 0.5f && e > 0.4f) FBDAT_out=vec3(0.0,0.3,0.5);
    if(e <= 0.6f && e > 0.5f) FBDAT_out=vec3(0.0,0.5,1.0);
    if(e <= 0.7f && e > 0.6f) FBDAT_out=vec3(0.5,0.0,0.0);
    if(e <= 0.8f && e > 0.7f) FBDAT_out=vec3(0.2,0.5,0.2);
    if(e <= 0.9f && e > 0.8f) FBDAT_out=vec3(0.5,0.5,0.0);
    if(e <= 1.0f && e > 0.9f) FBDAT_out=vec3(0.0,0.3,0.0);
    if(e <= 1.2f && e > 1.0f) FBDAT_out=vec3(0.0,0.5,0.5);
    if(e > 1.2f) FBDAT_out=vec3(0.0f,0.3,0.3);

}
//void color(float e, out vec3 O){
//    if(e <= 0.3 && e > 0.0f) {FBDAT_out=vec3(1.0/e,0.0,0.0);}
//    if(e <= 0.6 && e > 0.3f) FBDAT_out=vec3(0.0,1.0/e,0.0);
//    if(e <= 0.9f && e > 0.6f) FBDAT_out=vec3(0.0,0.0,1.0/e);
//    if(e <= 1.2f && e > 0.9f) FBDAT_out=vec3(0.5,0.3,0.0);
//    if(e > 1.2f) FBDAT_out=vec3(0.0f,0.3,0.5);
//
//}
void toCart( float r,  float theta, float rDot, float thetaDot, out vec3 pos, out vec3 vel_in){
    pos.y = r * sin(theta);
    pos.x = r * cos(theta);
    vel_in.x = rDot * cos(theta) -  r * thetaDot * sin(theta);
    vel_in.y = rDot * sin(theta) +  r * thetaDot * cos(theta);
}

void toPolar( vec3 POS, vec3 VEL, out float R, out float THETA, out float RDOT, out float THETADOT)
{

    RDOT = ((POS).x * (VEL).x + (POS).y * (VEL).y)/sqrt((POS).x * (POS).x + (POS).y * (POS).y );
    THETADOT = ((POS).x * (VEL).y - (POS).y * (VEL).x)/((POS).x * (POS).x + (POS).y * (POS).y );
    THETA = atan((POS).y,(POS).x);
    if (THETA < 0.0) THETA += 2.0 * pi;
    R = length(vec2((POS).x,(POS).y));
}
vec3 calculateLRL(in vec3 p,in vec3 v, in float k){
    return cross( v, (cross(p,v))) - k*p/length(p);
}
float TrapRule(in float q,in  float qD ,in float qDD,in float qDDD,in float DT){
    float qA =q + qD * DT + 0.5 * qDD * DT * DT + 1.0/6.0 * qDDD* DT * DT* DT;
    return qA;
}
float test(float oldCord,float newCord,float denom, float multiplier){
    return multiplier*(length(oldCord)-length(newCord)/denom);
}
float calcPsi(in float psi,in  float thetaDot ,in float thtDD,in float thetaJerk,in float dt,in float rotDirection){
    float newPsi;
    if(rotDirection < 0.0){
        thtDD *= -1.0f;
        newPsi= -1.0f * TrapRule(psi,thetaDot,thtDD,thetaJerk,dt);
    }
    if(rotDirection > 0.0) newPsi = TrapRule(psi,thetaDot,thtDD,thetaJerk,dt);
    return newPsi;
}
void calcOrbit(in vec3 pos,in vec3 vel,in float alpha,in float dt, out vec3 posResult,out vec3 velResult, out vec3 FBDATA_OUT){
    float L, e, psi, newPsi, rDD, thtDD, toOrAway, rotDirection, sizePsi;
    float r, theta, thetaDot, rDot;
    vec3 LRL;
    toPolar(pos, vel, r, theta, rDot, thetaDot);
    vel.x = rDot * cos(theta) -  r * thetaDot * sin(theta);
    vel.y = rDot * sin(theta) +  r * thetaDot * cos(theta);
    L = length((cross(pos, vel)));
    ////LRL constant that points to point at which the masses are closest: momentum X (position X momentum) - mkR
    LRL = calculateLRL(pos, vel, alpha);
    ////r=(L/mass)^2/GM * 1/cos(1-ecos(psi)) e defines shape of orbit and const through out
    e = length(LRL)/(alpha);
    ////this is neg when angle between L & position > PI/2
    sizePsi =dot(LRL, pos);
    //// defines sign of thetadot
    rotDirection = (cross(pos, vel)).z;
    ////defines  weather the body is approaching or moving away need b/c orbits are semetrical for pos and speed
    toOrAway = 1.0f * sign((cross(LRL, pos)).z);
    ////solve orbit eq for psi the angle between position and rmin
    psi = (asin((cross(LRL/length(LRL), pos/length(pos))).z));
    if (isnan(psi)) psi = pi/2.0 * toOrAway;
    if (toOrAway < 0.0f && sizePsi < 0.0f)psi = -pi - psi;
    if (toOrAway > 0.0f && sizePsi < 0.0f)psi = pi - psi;
    thtDD = -2.0*L*rDot/(r*r*r);
    //    rDD = k/L*cos(psi)*length(thetaDot);
    rDD = thetaDot*thetaDot * r - alpha/(r*r);
    r = TrapRule(r, rDot, rDD, 0.0, dt);
    newPsi= calcPsi(psi, thetaDot, thtDD, 0.0, dt, rotDirection);
    rDot = alpha / L * e * sin(newPsi);
    theta = TrapRule(theta, thetaDot, thtDD, 0.0, dt);
    thetaDot = L/(r*r)*sign(thetaDot);

    if (dot(LRL, pos) < 0.0 && (cross(pos, LRL)).z == 0.0) psi = pi;
    if (dot(LRL, pos) > 0.0 && (cross(pos, LRL)).z == 0.0) psi = 0.0;
    color(e,FBDATA_OUT);

    toCart(r, theta, rDot, thetaDot, posResult, velResult);

}
void main() {

    //seeker
    float seekX = -0.5+(seeker.y/ 100.0f);
    float seekY = (seeker.z/ 100.0f);
    float seekZ = seeker.z;

    //settings
    int touchOn = 1;
    int emmiterOn = 1;
    float resetVelocity =1.0f*pow(10.0f, 11.0f);
    float worldScale = 0.4f*pow(10.0f, -6.0f);
    float dt = 2.3f*pow(10.0f, -15.0f);
    float alpha = -250.0*pow(10.0f, 4.0f)*seekX;
    float posInZ,velInZ;

    posInZ = pos_in.z;
    velInZ = vel_in.z;
    initPos_out = initPos_in;
    FBDAT_out = FBDAT_in;

    vec3 vel = vec3(vel_in.xy, 0.0f);
    vec3 pos = vec3(pos_in.xy, 0.0f);
    if (touchOn == 1) pos.xy = pos.xy - vec2(time.xy);


    //RESET p > 10 posin
    if(length(pos_in.xy) >= 10.0f){
        pos = vec3(touch.xy-time.xy,0.0);
        vel = vec3(0.0f, 1.0f, 0.0f)*vel_in.z;
        velInZ = 1.0f*vel_in.z;
    }
    //INIT pos -1 touch
    if(0.0 > posInZ && posInZ> -1.4){
        posInZ= 1.0;
        pos = vec3(touch.xy-time.xy,0.0f);
        vel = vec3(0.0f, 1.0f, 0.0f)*vel_in.z;
        velInZ = 1.0f*vel_in.z;
    }


    //REFLECT p > 0 r < planet
    if (time.z >= length(pos.xy) && posInZ > 0.0){
        vec3 normal =  vec3(pos.xy,0.0);
        normal = normal/length(normal);
        vel = vel - 2.0* dot(vel,normal)*normal;
        pos = pos*1.01;

    }
    ////CALC ORBIT p > 1.0 pos
    if(posInZ > 0.0f&&time.z <= length(pos.xy)){

        pos =  pos * worldScale;
        vel =  vel*worldScale ;
        calcOrbit(pos ,vel, alpha, dt, pos, vel, FBDAT_out);
        vel = vel/worldScale;
        pos = pos/worldScale;
        pos.z = 1.0f;

    }

if (pos_in.z > -3.5 &&  -1.5 > pos_in.z ){
    initPos_out =vec3(time.xy,0.0);
}

    if (touchOn == 1) pos.xy = pos.xy + vec2(time.xy);
    pos_out = vec3(pos.xy, posInZ);
    vel_out = vec3(vel.xy, velInZ);
}

//\0
