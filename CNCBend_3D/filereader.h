#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
#include "sysglobalvars.h"
#include "math.h"
#include <QFile>
#define BEND_SURFACE_DIFFER  6.00
class fileReader
{
public:
    fileReader();
    ~fileReader();
protected:
    GLData *readOriginFile(QString path);
    //对各种数据结构操作函数
    trimmed_surface_type *transform_Brep(gl_data *pHead);
    int modifyGeneratrix(bend_surface *pbend);
    void convertOriginToXY(bend_surface *pHead);
    bend_surface *getWorkPieceInfo(trimmed_surface_type *pTrimmed);
    float getBendAngle(trimmed_surface_type *pSurface);
    QVector<trimmed_surface_type *>findTrimmedSurface(trimmed_surface_type *pTrimmed, trimmed_surface_type *pHead);
    QVector<trimmed_surface_type *>findSideSurface(trimmed_surface_type *pCur, trimmed_surface_type *pHead);
    bool judgeLineEqual(line_type *pline1,line_type *pline2);
    bool judgeXformEqual(xform_type form1,xform_type form2);
    void computeSurfaceNormal(stu_polygon *pPolygon, point3f &normal);
    void computeTrimmedNormal(trimmed_surface_type *ptrimmed, point3f &normal);
    void getThickAndRadiusAndAngle(bend_surface *pHead);
    point3f getDeploy_off(bend_surface *pbend, basic_surface *pBasic1, basic_surface *pBasic2);
    void convertToDeploy(bend_surface *pHead);
    void setTrimmedData(trimmed_surface_type *pSurface, trimmed_surface_type *pSurface_pa);
    stu_polygon *formDeploySurface(bend_surface *pbend);
    void formSideSurface(bend_surface *pBend);


    nurbsSurface_type *formRevolution(line_type generatrix, line_type axis, float start_angle, float end_angle);
    gl_data *findGLData(int pos, gl_data *pHead);
    bend_surface *findBendSurface(int bendnum,bend_surface *pHead);

    void setBendTopFlag(bend_surface *pbend,bend_surface *pHead);

    float Y_bendDepth(float bendAngle);

    //矩阵变换,矩阵运算,板料计算
    void EquationGroup(point3f &off, xform_type matrix);
    void xform_matrix(xform_type *pForm, point3f &point);
    void xform_matrix(xform_type *pForm, float &x_pos,float &y_pos,float &z_pos);
    void convertWork_Part(xform_type *pForm,bend_surface *pHead, bend_surface *pBend, basic_surface *pBasic, bool isTop);
    void MatrixPartConvert(xform_type *pForm,bend_surface *pHead,bend_surface *pBend,basic_surface *pBasic,bool isTop);
    void MatrixTotalConvert(bend_surface *pHead, xform_type *pForm, bool isTop);
    void convertOutLineSurface(xform_type *pForm, trimmed_surface_type *pSurface);
    void formBendedData(int bendnum,bool isTop,bend_surface *pHead);
    void formBendSideSurface(int bendnum, bend_surface *pHead);
    nurbsSurface_type *formSideNurbsSurface(nurbsSurface_type *pSurface, nurbsSurface_type *pSurface_pa, bool bFont);

    xform_type *formRevolutinMatrix(point3f axis, float angle,point3f off);
    xform_type *formTranslationMatrix(point3f off);
    xform_type *MatrixMultiply(xform_type *pForm1,xform_type *pForm2);
    xform_type *computeMatrix(point3f source, point3f dest);
    xform_type *computeInverseMatrix(xform_type *pForm);
    xform_type *formTurnAboutMatrix(int bendnum,bend_surface *pHead);
    float computeDeterminant(float a[3][3]);

    //重置类函数
    void resetToolFlag(trimmed_surface_type *pTrimmed);
    void resetVisitFlag(bend_surface *pHead);

    //各种析构函数
    void destroyTrimmed(trimmed_surface_type *pTrimmed);
    void destroyNurbsSurface(nurbsSurface_type *pNurbs);
    void destroyEntity(gl_data *pHead);

    //各种干涉判断函数
    bool InterFereWithTools(trimmed_surface_type *pPart, bend_surface *pHead);
    bool InterFere_trimmed_surface_With_Face(trimmed_surface_type *pTrimmed, stu_polygon *pPolygon);
    bool InterFere_Face_With_Face(stu_polygon *pPolygon1, stu_polygon *pPolygon2);
    bool InterFere_Line_With_Surface(line_type *pLine, stu_polygon *pPolygon);
    bool judgePointOnSurface(point3f point, stu_polygon *pPolygon,point3f normal);
    void recoverBendData(int bendnum,bend_surface *pHead,int tag);

protected:
    int fileType;       //0为Pro/e,1为SolidWorks
    int bendNum;       //折弯总道数
    float thickness;
    QString fileName;
};

#endif // FILEREADER_H
