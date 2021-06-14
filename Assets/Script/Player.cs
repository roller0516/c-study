using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Player : MonoBehaviour
{
    public Animator ani;
    public Camera camera;
    public NavMeshAgent agent;

    bool isMove;
    bool isFind;

    float MaxDistance = 10;
    float angle;

    Vector3 destPos;

    private void Awake()
    {
        camera = Camera.main;
    }

    void Start()
    {
        angle = 0.0f;
        ani = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
        agent.updateRotation = false;
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetMouseButton(1))
        {
            Vector3 x;

            x.x = Input.mousePosition.x;
            x.y = Input.mousePosition.y;
            Ray ray = camera.ScreenPointToRay(new Vector3(x.x, x.y, 0));
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                SetDestPos(hit.point);
            }
        }
        else 
        {
            RaycastHit hit2;
            if (Physics.Raycast(transform.position, transform.forward, out hit2, MaxDistance))
            {
                if (hit2.transform.gameObject.tag == "Monster")
                {
                    ani.SetInteger("StateIndex", 2);
                    print("hit");
                    Debug.DrawRay(transform.position, transform.forward * MaxDistance, Color.red, 0.3f);
                }
            }
        }
        
        

        if (isMove)
            Move();
            
    }

    void Move() 
    {
        if (agent.velocity.magnitude == 0.0f) 
        {
            isMove = false;
            ani.SetInteger("StateIndex", 0);
            return;
        }
        ani.SetInteger("StateIndex", 1);
        var dir = new Vector3(agent.steeringTarget.x, this.transform.position.y,
            agent.steeringTarget.z) - this.transform.position;
        this.transform.forward = dir;
    }
    void SetDestPos(Vector3 dest) //µµÂøÁöÁ¡
    {
        agent.SetDestination(dest);
        destPos = dest;
        isMove = true;
    }
    
}
