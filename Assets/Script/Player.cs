using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Player : MonoBehaviour
{
    public float MaxDistance;

    public int playerAttack;

    NavMeshAgent agent;
    new Camera camera;
    Animator ani;
    GameObject target;

    bool isMove;
    bool isFind;

    RaycastHit hit;

    Vector3 destPos;

    private void Awake()
    {
        camera = Camera.main;
    }

    void Start()
    {
        ani = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
        playerAttack = 10;
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetMouseButton(1))
        {
            Vector3 x;

            x.x = Input.mousePosition.x;
            x.y = Input.mousePosition.y;

            Ray ray = camera.ScreenPointToRay(new Vector3(x.x, x.y, 0));//¹Ù´Ú

            if (Physics.Raycast(ray, out hit))
            {
                if (hit.transform.gameObject.tag == "Monster")
                {
                    target = hit.transform.gameObject;
                    isMove = false;
                    SetDestPos(target.transform.position);
                }
                else 
                {
                    SetDestPos(hit.transform.position);
                    //agent.isStopped = false;
                }
            }
        }


        if (isMove)
            Move();
        if(isFind)
            Attack();
    }

    void Move() 
    {
        if (agent.velocity.magnitude == 0.0f) 
        {
            isMove = false;
            ani.SetInteger("StateIndex", 0);
            //agent.isStopped = true;
            return;
        }
        if (Vector3.Distance(target.transform.position, this.transform.position) < MaxDistance)
        {
            isFind = true;
            agent.speed = 0;
            return;
        }
        ani.SetInteger("StateIndex", 1);
        var dir = new Vector3(agent.steeringTarget.x, this.transform.position.y,
            agent.steeringTarget.z) - this.transform.position;
        this.transform.forward = dir;
    }

    void Attack() 
    {
        ani.SetInteger("StateIndex", 2);
    }
    void SetDestPos(Vector3 dest) //µµÂøÁöÁ¡
    {
        agent.SetDestination(dest);
        destPos = dest;
        isMove = true;
    }
    
}
