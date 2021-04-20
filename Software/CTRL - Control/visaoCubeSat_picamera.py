from picamera.array import PiRGBArray
from picamera import PiCamera
from scipy.spatial import distance as dist
import cv2
import numpy as np
import time
 
#captura o video da camera
cam = PiCamera()
cam.resolution = (480, 320)
cam.framerate = 10
rawCapture = PiRGBArray(cam, size=(480, 320))

time.sleep(1)

for frame in cam.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    
    #Le o frame e a coloca em uma variavel
    img = frame.array

    
    #define o centro da camera pegando as dimensoes da imagem
    #e dividindo por 2
    camera_center = (240, 160)
    
    #converte a imagem para tons de cinza
    imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    #aplica um blur sobrea a imagem
    imgGray = cv2.medianBlur(imgGray,5)
    
    #usa a imagem convertida para gerar uma imagem binarizada
    #ret, binaryImg = cv2.threshold(imgGray,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)        
    binaryImg = cv2.adaptiveThreshold(imgGray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 3, 2) 
    #inverte a binarizacao da imagem para o contorno nao detectar a borda do frame       
    binaryImg = 255 - binaryImg
    
    binaryImg = cv2.morphologyEx(binaryImg, cv2.MORPH_OPEN, (5,5))

    #Encontra os contornos externos da imagem binarizada
    _, contours, _ = cv2.findContours(binaryImg, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    
    circular_contours = list()
    other_contours = list()
    #
    #Separa contornos circulares de nao circulares
    #
    for c in contours:
        approx = cv2.approxPolyDP(c,0.01*cv2.arcLength(c,True),True)
        area = cv2.contourArea(c)
        if ((len(approx) > 4) & (area > 30)):
            circular_contours.append(c)
        else:
            other_contours.append(c)
            
    #
    #deteccao dos centroides em objetos circulares
    #
    circular_centers = list()
    for c in circular_contours:
        #encontra os momentos dos contornos
        M = cv2.moments(c)
        #usa os momentos para calcular os centroides
        if M["m00"] == 0:
            M["m00"] = 1
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        circular_centers.append(cX)
        circular_centers.append(cY)
        
         #desenha os marcadores na imagemcv2
        cv2.drawContours(img, [c], -1, (0, 0, 255), 2)
        cv2.circle(img, (cX, cY), 7, (255, 255, 0), -1)
        cv2.putText(img, "Sun", (cX - 20, cY - 20) ,cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
     
    #
    #centroides em objetos nao circulares
    #
    other_centers = list()
    for c in other_contours:
        #encontra os momentos dos contornos
        M = cv2.moments(c)
        #usa os momentos para calcular os centroides
        if M["m00"] == 0:
            M["m00"] = 1
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        if cX not in circular_centers:
            other_centers.append(cX)
            other_centers.append(cY)
            
            #desenha os marcadores na imagemcv2
            cv2.drawContours(img, [c], -1, (255, 0, 0), 2)
            cv2.circle(img, (cX, cY), 7, (0, 255, 255), -1)
            cv2.putText(img, "Horizon", (cX - 20, cY - 20) ,cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
        
    #define o centro da camera
    cv2.circle(img, (int(camera_center[0]), int(camera_center[1])), 7, (255, 0, 255), -1)
        
    #se encontrou as posicoes, printa os calculos
    print("------RESULTADOS-----")
    if(len(camera_center) > 1 and len(other_centers) >1 and len(circular_centers) >1): 
        #Calcula a distancia do centro da camera ate a linha do horizonte
        distance_center2Hor = dist.euclidean((camera_center[0], camera_center[1]), (other_centers[0], other_centers[1]))
        print("Distancia do Centro ao Horizonte : "+  str(distance_center2Hor))
        cv2.line(img,(int(other_centers[0]),int(other_centers[1])),(int(camera_center[0]), int(camera_center[1])),(255,0,0),1)
        #define um ponto logo acima do centroide do horizonte
        up_point = other_centers[1] - 100
        cv2.line(img,(int(other_centers[0]),int(other_centers[1])),(int(other_centers[0]), int(up_point)),(255,0,0),1)
         
        #Calcula a distanca do centro da camera ate o  centro do sol
        distance_center2Sun = dist.euclidean((camera_center[0], camera_center[1]), (circular_centers[0], circular_centers[1]))
        print("Distancia do Centro ao Sol : " + str(distance_center2Sun))
        cv2.line(img,(int(circular_centers[0]),int(circular_centers[1])),(int(camera_center[0]), int(camera_center[1])),(255,0,0),1)
       
        #calcula as diferencas de coordenadas e deixa os valores positivos
        dist_x = other_centers[0] - camera_center[0]
        dist_x = dist_x**2
        dist_x = np.sqrt(dist_x)
        dist_y = camera_center[1] - other_centers[1]  
        dist_y = dist_y**2
        dist_y = np.sqrt(dist_y)
            
        #Calcula o angulo entre a reta que vai do centro da camera ao centro
        #da linha do horizonte e a reta vertical que passa pelo centro da
        #linhda do horizonte
        angle_degrees = np.arctan(dist_x/dist_y)*180/np.pi
        if camera_center[1] > other_centers[1]:
            angle_degrees = 180 - angle_degrees
            
        #Print dos resultados
        print("Camera : " + str(camera_center[0]) + ", " + str(camera_center[1]))
        print("Horizonte : " + str(other_centers[0]) + ", " + str(other_centers[1]))
        print("Sol : " + str(circular_centers[0]) + ", " + str(circular_centers[1]))
        print("Angulo Camera/horizonte : " +  str(angle_degrees) + " graus")
            
    #Exibe as imagens
    cv2.imshow("Binary",binaryImg)     
    cv2.imshow("Resultado",img)     
    key = cv2.waitKey(1) & 0xFF
        
    rawCapture.truncate(0) 
        
    if key == ord("q"):
         break
                
cv2.destroyAllWindows()
